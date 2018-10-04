/* written 2009 by A. Christ
/  released under GNU General Public License
/
/  I appreciate any feedback, including bug reports, feature requests and whether
/  you found this widget useful at all.
/
/  e-mail: software@quantentunnel.de
/          (mandatory to include QTechSpinBox in the subject line to bypass spam filter)
*/

/* possibilities for optimization:
   - textFromValue: simplified if conditions for rounding rules (although compiler might take care of)
   - store locale() derived minusSign, decimalPoint, exponential, regExp in private data members
*/

/* change done by Sylvain Martin :
- add the stepInUnit option, because in the everyday life we do not sweep the power of ten (the order of magnitude)
	but the number before it.
- change singlestep in double (instead of unsigned short int) because the integer is not really justified here
*/
#include "qtechspinbox.h"

#include <QtGui>
#include <QtCore>

#include <QLineEdit>
#include <QLocale>
#include <QRegExpValidator>
#include <QDebug>
#include <math.h>
#include <limits>

// Sylvain Martin: I removed this part, because it's not compile and it'snt really needed ...
//// see math.h for following workaround of float bug in msvc library (is this really needed?)
//#define __DEFINE_FLOAT_STORE_MATHFN_D2(fn2)	\
//static __inline__ double			\
//__float_store_ ## fn2 (double x, double y)	\
//{						\
//  __volatile__ double res = (fn2) (x, y);	\
//  return res;					\
//}

//#undef pow
///* Define the ___float_store_pow function and use it instead of pow().  */
//__DEFINE_FLOAT_STORE_MATHFN_D2 (pow)
//#define pow __float_store_pow

const int lowestPrefix(-24);
const int highestPrefix(24);
const QChar unitPrefix[] = {QLatin1Char('y'), QLatin1Char('z'), QLatin1Char('a'), QLatin1Char('f'), QLatin1Char('p'), QLatin1Char('n'), QChar(0x03BC),
                            QLatin1Char('m'), QLatin1Char(' '), QLatin1Char('k'), QLatin1Char('M'), QLatin1Char('G'), QLatin1Char('T'), QLatin1Char('P'),
                            QLatin1Char('E'), QLatin1Char('Z'), QLatin1Char('Y')};

/*!
    \class QTechSpinBox
    \brief QTechSpinBox is a spin box widget with exponential notation

    \ingroup input widgets
    \mainclass

    QTechSpinBox allows user to set double values in exponential notation
    If no exponential notation is needed, QDoubleSpoinBox from Qt can be used;
    if scientific notation, but neither units nor technical notation is needed,
    QScienceSpinBox from Matthias Pospiech (http://www.matthiaspospiech.de).

    QTechSpinBox allows the user to choose a value by clicking the up/down
    buttons or pressing up/down on the keyboard to increase/decrease
    the value currently displayed. The user can also type the value in
    manually.

    The displayed value can be appended with arbitrary strings indicating
    the unit. If three digits are allowed in front of the decimal sign, the
    unit will be displayed with unit modifiers (milli, kilo, micro, Mega and so on).
    The value retrieved by value() factors the unit modifier in. If a textual
    representation is needed, the value can be formatted using textFromValue().

    When entering data manually, all entries acceptable as output (i.e., number of
    pre- and postdigits, unit) are allowed. In addition, exponents and unit modifier
    (with unit, unless empty) may be combined.  E.g., if unit is m (meter) and
    '3e12 nm' or '3e12 n' is entered, it will be formatted to '3 km' (if
    predigits == 3 and modifierunits == true) or '3e3 m' (otherwise).
    Ambiguity resolution: units and unit modifier might be ambiguous (e.g., 'P'
    could be first letter of Pa (pascal, unit for pressure) or unit modifier for
    Penta (10^15). In such cases it is interpreted as pascal. This only applies if
    the baseunit starts with one of the letters used as unit prefix. In these cases,
    at least the first letter of the base unit needs to be included (e.g., PP for
    pentapascal, fully qualified unit would be PPa).

    Every time the value changes QTechSpinBox emits valueChanged() signals.
    If only the textual representation changes, valueChanged(string)is emitted.
    The current value can be fetched with value() and set with setValue().

    Clicking the up/down buttons or using the keyboard accelerator's up and down
    arrows will increase or decrease the current value by factors of size singleStep().
    If you want to change this behaviour you can reimplement the virtual function
    stepBy(). The minimum and maximum value and the step size can be changed with
    setMinimum(), setMaximum() and setSingleStep().

    \sa QDoubleSpinBox
*/

/*!
    \fn void QSpinBox::valueChanged(double i)

    This signal is emitted whenever the spin box's value is changed.
    The new value's double value is passed in \a i.
*/

/*!
    \fn void QSpinBox::valueChanged(const QString &text)

    The new text representation is passed literally in \a text
    whenever it is changed. this includes situation with no change of
    the double value (i.e., when formatting is changed).
*/

/*!
   Constructs a spin box with initial value 0.0. It is parented to \a  parent.
   Default settings:
   \table 100%
    \row \o maximum
         \o platform dependent
         \o highest value allowed for double
    \row \o minimum
         \o platform dependent
         \o lowest (i.e. most negative) value allowed for double
    \row \o singlestep
         \o 10
         \o factor by which a single up or down click increases or decreases
    \row \o predigits
         \o 3
         \o maximal digits of mantissa in front of decimal sign (reasonable is 0, 1 or 3)
    \row \o postdigits
         \o 2
         \o maximal digits of mantissa after decimal sign
    \row \o baseunit
         \o empty string
         \o if non-empty, unit prefixes (milli, kilo, micro, ...) will be prepended
    \row \o roundingrule
         \o Arithmetic
         \o rounding rule for mantissa
    \endtable
    \sa setMinimum(), setMaximum(), setSingleStep(), setBaseUnit(), setPostdigits(), setPredigits(), setRoundingRule()
*/

QTechSpinBox::QTechSpinBox(QWidget *parent) : QAbstractSpinBox(parent),
   d_minimum(-std::numeric_limits<double>::max()), d_maximum(std::numeric_limits<double>::max()),
   d_value(0), singleStepDbl(1), baseunitString(QLatin1String("")), postdigitsInt(2), predigitsInt(3),
   roundingruleEnum(Arithmetic),stepInUnitBool(true),predigitsClassicalInt(3),postdigitsClassicalInt(2){

   Q_ASSERT(value() > d_minimum && value() < d_maximum);
   Q_ASSERT(highestPrefix % 3 == 0);
   Q_ASSERT(lowestPrefix % 3 == 0);
   Q_ASSERT(sizeof(unitPrefix)/sizeof(unitPrefix[0]) == (highestPrefix - lowestPrefix) / 3 + 1);

   // we set up the context menu
   setupMenu();


   setRegExpValidator();
   connect(this, SIGNAL(editingFinished()), this, SLOT(setValueFromText()));


}

//------------------------------------------------------------------------
// Setter functions

/*!
    \property QTechSpinBox::predigits
    \brief number of digits in front of decimal sign

    If above 1, the exponent will only take values divisible by predigits.
    This is often used to force exponent to only take values of 3, 6, 9, ...
    that can be represented by unit modifers (kilo, Mega, nano, ...). Setting
    predigits to 0 or 1 is a question of personal preference ('x = -.5' versus
    'x = -0.5'). While values other than 0, 1 and 3 are acceptable, I do not
    see why anybody would want this.

    It is enforced that predigits + postdigits is > 0.
*/

void QTechSpinBox::setPredigits(const unsigned short &predigits){
   if (predigits > 0 || postdigitsInt > 0){
      predigitsInt = predigits;
	  predigitsClassicalInt = predigits;
      setRegExpValidator();}}

/*!
    \property QTechSpinBox::unitmodifiers
    \brief option to display unit modifiers (milli, Giga, ...)

    If true and predigits is set to 3, then unit modifers (kilo, Mega, ...)
    will be used instead of exponential notation. If predigits != 3, then
    this setting will be ignored.
*/

void QTechSpinBox::setUnitModifiers(bool useModifiers){
   if (unitmodifiersBool != useModifiers){
      unitmodifiersBool = useModifiers;
      updateDisplay();}}

/*!
    \property QTechSpinBox::postdigits
    \brief number of digits after decimal sign

    Rounding occurs as specified by roundingrule. Note that the total
    precision depends also on predigits. The underlying double value is
    not truncated. E.g. if 12.3 is stepped up by factor 10, a value like
    122.7 may result if this is what was entered earlier.
    It is enforced that predigits + postdigits is > 0.

    /sa setRoundingRule()
*/

void QTechSpinBox::setPostdigits(const unsigned short &postdigits){
   if (postdigits > 0 || predigitsInt > 0){
      postdigitsInt = postdigits;
	  postdigitsClassicalInt = postdigits;
      setRegExpValidator();}}

/*!
    \property QTechSpinBox::singlestep
    \brief step size when clicking up or down

    Up multiplies by this factor, down divides. Unless original
    value is 0, in which case 1 or -1 is produced.
*/

void QTechSpinBox::setSingleStep(const double &singlestep){
   singleStepDbl = singlestep == 0 ? 1 : singlestep;}

/*!
    \property QTechSpinBox::baseunit
    \brief measuring unit, e.g., gram, mol, N/m

    Do not include any modifier (milli, tera, ...)
*/

void QTechSpinBox::setBaseUnit(const QString &baseunit){
   baseunitString = baseunit;
   setRegExpValidator();}

/*!
    \property QTechSpinBox::value
    \brief the value of the spin box

    setValue() will emit valueChanged() if the new value is different
    from the old one.
*/

void QTechSpinBox::setValue(double n_value){
   if (n_value >= minimum() && n_value <= maximum() && value() != n_value){
      d_value = n_value;
      emit valueChanged(value());
      updateDisplay();}}

/*!
    \property QTechSpinBox::minimum
    \brief lowest value of the spin box

    Lowest value, often negative, that the spinbox accepts. It is enforced that
    this value is below maximum().
*/

void QTechSpinBox::setMinimum(double n_minimum){
   if (n_minimum <= value()) d_minimum = n_minimum;}

/*!
    \property QTechSpinBox::maximum
    \brief highest value of the spin box

    Highest value that the spinbox accepts. It is enforced that
    this value is below minimum().
*/

void QTechSpinBox::setMaximum(double n_maximum){
   if (n_maximum >= value()) n_maximum = d_maximum;}

/*!
    \property QTechSpinBox::roundingrule
    \brief method to round mantissa to requested precision

    Requested precision depends on predigits and postdigits, and is value
    dependend if predigits is >1. As long as the value is modified by up and
    down arrows, hidden digits are preserved. As soon as the spin box is left
    or text is entered manually, the precision is deduced from the actual text.
    Roundingrule can be set to Cut (no rounding occurs), Arithmetic (0.5
    is rounded up to 1, 1.5 to 2, -1.5 to -1), Symmetric (as Arithmetic but
    e.g., -1.5 is rounded to -2), or BankersRule (to even number: 1.5 -> 2,
    2.5 -> 2, 3.5 -> 4)
*/

void QTechSpinBox::setRoundingRule(const Roundingrule& n_roundingrule){
   roundingruleEnum = n_roundingrule;
   updateDisplay();}

// 

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void QTechSpinBox::stepBy(int steps)
///
/// \brief	do a \c steps up or down .
///
/// \author	A. Christ && Sylvain Martin
/// \date	30/10/2012
///
/// \param	steps number of steps.
////////////////////////////////////////////////////////////////////////////////////////////////////
void QTechSpinBox::stepBy(int steps){
   Q_ASSERT(singleStep() > 0);

   if(stepInUnitBool && unitmodifiersBool && predigitsInt==3){

		   double val = value();
		   int i =0;
		   while ((fabs(val)>10.0)){
			   val = val/10.0;
			   i++;
		   }

		   int unitRange = i%3;
		   double tmpVal = value() - singleStep()*steps*pow(10.0,i-unitRange);

		   if(tmpVal>d_minimum && tmpVal < d_maximum)  setValue(tmpVal);

   }else if(stepInUnitBool){

	   double val = value();
	   int i =0;
	   while ((fabs(val)>10.0)){
		   val = val/10.0;
		   i++;
	   }
	   double tmpVal = value() - singleStep()*steps*pow(10.0,i-predigits());

	   if(tmpVal>d_minimum && tmpVal < d_maximum)  setValue(tmpVal);

   }else{

   double newValue(value());
   if (steps != 0){

      if (newValue == 0) newValue = steps < 0 ? -1 : 1;

      // take care of possible double overflow in case of many steps and/or large singleStep
      else if (steps > 0) try {for (int i(0); i < steps; ++i) newValue *= singleStep();}
                          catch (...) {newValue = maximum();}

      else try {for (int i(0); i > steps; --i) newValue /= singleStep();}
           catch (...) {newValue = minimum();}
   }
   setValue(newValue);
   }
}

QAbstractSpinBox::StepEnabled QTechSpinBox::stepEnabled() const{
   QAbstractSpinBox::StepEnabled stepFlag(QAbstractSpinBox::StepNone);
   if (value() > minimum()) stepFlag |= QAbstractSpinBox::StepDownEnabled;
   if (value() < maximum()) stepFlag |= QAbstractSpinBox::StepUpEnabled;
   return stepFlag;}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString QTechSpinBox::textFromValue(double value) const
///
/// \brief	text <-> value conversions and validations
///
/// \author	A. Christ
///
////////////////////////////////////////////////////////////////////////////////////////////////////
QString QTechSpinBox::textFromValue(double value) const{
   // string with at least sufficient numer of digits, separated in mantissa and exponent
   
   QString str = locale().toString(value, 'e', postdigitsInt + predigitsInt + 2);
   int exponent = str.section(locale().exponential(), 1, 1).toInt();
   str = str.section(locale().exponential(), 0, 0); //mantissa (could be negative) with decimal sign
   int signSpace_1(str.at(0) == locale().negativeSign() ? 1 + 1 : 0 + 1); // current position of dec'point
   Q_ASSERT(str.contains(locale().decimalPoint()));
   str = str.remove(locale().decimalPoint());                           // remove delimiter (normally '.' or ',')
   // determine new position of decimal sign, and position correctly
   int shiftDelimiter;
   switch (predigitsInt){
      case 0:
         shiftDelimiter = -1;  //remove standard single digit in front of delimiter
         break;
      case 1:
         shiftDelimiter = 0;
         break;
      default:
         if (exponent >= 0) shiftDelimiter = exponent % predigitsInt;
         else {
            shiftDelimiter = abs(exponent) % predigitsInt;
            if (shiftDelimiter > 0) shiftDelimiter = predigitsInt - shiftDelimiter;}
         break;}
   exponent -= shiftDelimiter;
   int str_size = shiftDelimiter + signSpace_1 + postdigitsInt;
   Q_ASSERT(str.size() > (str_size + 1));    // at least two digits more than needed, to allow rounding
   unsigned short int cutDigit(locale().toInt((str.at(str_size))));
   unsigned short int followingDigit(locale().toInt(str.at(str_size+1)));
   str.resize(str_size);
   qlonglong mantissaInt(locale().toLongLong(str));
   switch (roundingruleEnum){
   // should check that ALL following digits = 0 if cutDigit=5; for double: check only one following digit
      case Cut:
         break;
      case BankersRule:      // to even number
         if (cutDigit > 5 ||
            (cutDigit == 5 && followingDigit > 0) ||
            (cutDigit == 5 && followingDigit == 0 && (abs(mantissaInt) % 2) != 0)){
         mantissaInt >= 0 ? ++mantissaInt : --mantissaInt;}
         break;
      case Arithmetic:       // as symmetric, but -3.50 gives -3
         if (cutDigit > 5 ||
            (cutDigit == 5 &&  followingDigit > 0) ||
            (cutDigit == 5 && mantissaInt >= 0 && followingDigit == 0))
         mantissaInt >= 0 ? ++mantissaInt : --mantissaInt;
         break;
      case Symmetric:       // if cut digit is 5 or above; negative and positives are rounding oppositely
         if (cutDigit >= 5) mantissaInt >= 0 ? ++mantissaInt : --mantissaInt;
         break;}
   str = locale().toString(mantissaInt).trimmed();
   str = str.remove(locale().groupSeparator());
   //prepend '0' (locale-aware) to fill up to required number of digits (postdigits + 1)
   for (int i(str.size()); i < postdigitsInt + 1; ++i) str.prepend(locale().toString(0));
   if (postdigitsInt > 0) {
       /*
      Q_ASSERT_X(str.size() > shiftDelimiter + signSpace_1, str.toAscii(),
              QString("%1 + %2").arg(shiftDelimiter).arg(signSpace_1).toAscii());
      */
      str = str.insert(shiftDelimiter + signSpace_1, locale().decimalPoint());}
   if (!baseunitString.isEmpty() && predigitsInt == 3 && unitmodifiersBool == true &&
      exponent >= lowestPrefix && exponent <= highestPrefix){  // unit prefix
      Q_ASSERT_X(abs(exponent) % 3 == 0, "% 3 == 0", QString(exponent).toAscii());
      str = str + QChar(QLatin1Char(' ')) + QString(unitPrefix[(exponent - lowestPrefix) / 3] + baseunitString).trimmed();}
   else {
      str += QString(QLatin1String("%1%2")).arg(locale().exponential()).arg(locale().toString(exponent));
      if (!baseunitString.isEmpty()) str += QLatin1String(" ") + baseunitString;}
   return str;}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	double QTechSpinBox::valueFromText(const QString &text) const
///
/// \brief	This virtual function is used by the spin box whenever it needs to display the given value.
///
/// \author	A. Christ
///
////////////////////////////////////////////////////////////////////////////////////////////////////
double QTechSpinBox::valueFromText(const QString &text) const {
   double mantissa;
   int exponent(0);
   int firstNonNumeric(0);
   while (firstNonNumeric < text.size() && isNumeric(text.at(firstNonNumeric))) ++firstNonNumeric;
   bool ok;
   mantissa = locale().toDouble(text.left(firstNonNumeric), &ok);
   Q_ASSERT(ok);
   if (firstNonNumeric == text.size()) return mantissa;
   QString expString = text.mid(firstNonNumeric).trimmed(); //head of expString: e, unit, modifier
   if (expString.size() > 1 && expString.at(0) == locale().exponential() && isNumeric(expString.at(1))) {
      expString = expString.mid(1);    // cut 'e' or locale corresponding
      firstNonNumeric = 0;
      while (firstNonNumeric < expString.size() && isNumeric(expString.at(firstNonNumeric)))
                                                                                       ++firstNonNumeric;
      exponent = locale().toInt(expString.left(firstNonNumeric), &ok);
      Q_ASSERT_X(ok, "toInt", expString.toAscii());
      expString = expString.mid(firstNonNumeric).trimmed();}
   if (expString.size() > 0 && !baseunitString.startsWith(expString)){  // not only baseunit
      int unitNumber(0);
      while (unitPrefix[unitNumber] != expString[0]) ++unitNumber;
      Q_ASSERT_X(unitNumber <= (highestPrefix - lowestPrefix), "unit prefix not found: ", QString(expString[0]).toAscii());
      exponent += 3 * unitNumber + lowestPrefix;}
   mantissa = mantissa * pow((double)10, (double)exponent);
   return mantissa;}

void QTechSpinBox::setRegExpValidator(){
   // does lineEdit take over ownership of QRegExpValidator? is nowhere deleted!
   QString regExp = QString(QLatin1String("^%1?")).arg(QRegExp::escape(locale().negativeSign()));
   if (predigitsInt == 0) ;      // no digits prior to decimal sign
   else if (predigitsInt == 3 && !baseunitString.isEmpty()) regExp += QString(QLatin1String("\\d{1,3}"));
   else regExp += QString(QLatin1String("\\d{1,%1}")).arg(predigitsInt);
   // add optional decimalPoint and digits (digits mandatory, if decimalPoint present)
   if (postdigitsInt > 0) regExp += QString(QLatin1String("(%1\\d{1,%2})?")).arg(QRegExp::escape(locale().decimalPoint()))
                                                             .arg(postdigitsInt);
   // add optional exponent (incl negativeSign) and optional trailing space
   regExp += QString(QLatin1String("(e%1?\\d{1,3})? ?")).arg(QRegExp::escape(locale().negativeSign()));
   // add optional unit prefix, optional unit
   QString allUnitPrefixes(QLatin1String(""));
   for (int i(0); i <= (highestPrefix - lowestPrefix) / 3; ++i)
   if (!unitPrefix[i].isSpace()) allUnitPrefixes += unitPrefix[i];
   regExp += QString(QLatin1String(QLatin1String("[%1]?"))).arg(QRegExp::escape(allUnitPrefixes));
   if (!baseunitString.isEmpty()){   // allow any part from start of baseunit
      for (int i(0); i < baseunitString.size(); ++i)
                  regExp += QString(QLatin1String(QLatin1String("(%1"))).arg(QRegExp::escape(QString(baseunitString[i])));
      for (int i(0); i < baseunitString.size(); ++i) regExp += QLatin1String(")?");}
   regExp += QString(QLatin1String("$"));
   this->lineEdit()->setValidator(new QRegExpValidator(QRegExp(regExp), 0));
   updateDisplay();}

void QTechSpinBox::updateDisplay(){
   QString newString(textFromValue(value()));
   if (newString != lineEdit()->text()){
      lineEdit()->setText(newString);
      emit valueChanged(newString);}}

void QTechSpinBox::setValueFromText(){
   QString input(lineEdit()->text());  // copy needed as text() is const and validate() wants non-const
   int dummy(0);
   if (lineEdit()->validator()->validate(input, dummy) == QValidator::Acceptable)
                                                setValue(valueFromText(this->lineEdit()->text()));
   else /* QValidator::Intermediate, thus revert to original value */ updateDisplay();}

bool QTechSpinBox::isNumeric(QChar oneChar) const{
   QString allNumerics;
   QTextStream regExpStream(&allNumerics);
   regExpStream << locale().negativeSign() << locale().decimalPoint();
   for (unsigned short int i(0); i <= 9; ++i) regExpStream << locale().toString(i);
   return allNumerics.contains(oneChar);}

//------------------------------------------------------------------
// unclear functions. Needed at all?

QValidator::State QTechSpinBox::validate(QString &input, int &pos) const{
   Q_ASSERT_X(false, "QTechSpinBox::validate called", qPrintable(input));
   return QRegExpValidator::Invalid;}

void QTechSpinBox::fixup(QString &input) const{
   Q_ASSERT_X(false, "QTechSpinBox::fixup called", qPrintable(input));}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool QTechSpinBox::stepInUnit()
///
/// \brief	Determines if we can step in unit.
///
/// \author	Sylvain Martin
/// \date	30/10/2012
///
/// \return	true if it succeeds, false if it fails.
/// \sa unitmodifiers
/// \sa setUnitModifiers
/// 
/// If is true, the spin button changes the value of \a step time the \a unit \a modifier
/// or the power of ten. By example : 
/// \li if unitmodifiers is true and predigitsInt equal 3 if the current unit modifier 
/// 	is M (for Mega) and the \a step is 1, clicking on the spin button will add 1 Mega.
/// \li if unitmodifiers is false and  the current power of ten is 7 (10^7)
/// 	and the \a step is 1, clicking on the spin button will add 1x10^7.
////////////////////////////////////////////////////////////////////////////////////////////////////

bool QTechSpinBox::stepInUnit()
{
	return stepInUnitBool;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void QTechSpinBox::setStepInUnit( bool b )
///
/// \brief	set if the spin will \a stepping in unit.
///
/// \author	Sylvain Martin
/// \date	30/10/2012
///
/// \param	b	if true active the StepInUnit function.
/// 
/// \sa unitmodifiers
/// \sa setUnitModifiers
/// 	
/// If is true, the spin button changes the value of \a step time the \a unit \a modifier
/// or the power of ten. By example : 
/// \li if unitmodifiers is true and predigitsInt equal 3 if the current unit modifier 
/// 	is M (for Mega) and the \a step is 1, clicking on the spin button will add 1 Mega.
/// \li if unitmodifiers is false and  the current power of ten is 7 (10^7)
/// 	and the \a step is 1, clicking on the spin button will add 1x10^7.
////////////////////////////////////////////////////////////////////////////////////////////////////

void QTechSpinBox::setStepInUnit( bool b )
{
	stepInUnitBool =b;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void QTechSpinBox::contextMenuEvent(QContextMenuEvent *event)
///
/// \brief	(SLOT) Show a context menu. 
///
/// this context menu allows to change the step and the precision of this spin box.
////////////////////////////////////////////////////////////////////////////////////////////////////
void QTechSpinBox::contextMenuEvent(QContextMenuEvent *event)
{

	//setupMenu();

	// pour avoir la précision max : 0.00000 pour dispDecimals == 5
	QString strZero;
	if(singleStepDbl<1){
		strZero.fill('0', postdigits() - QString::number(singleStepDbl,'g',postdigits()).count() +2 );
	}else{
		strZero.fill('0', postdigits());
		strZero = "." + strZero;
	}

	txtStep->setText(QString::number(singleStepDbl,'g',postdigits())+strZero);
	// make the "InputMask" for values between 0 and 1000 with dispDecimals digits after the comma
	QValidator *inputRange = new QDoubleValidator(0, 1000, postdigits() , this);

	// set the "InputMask" to the txtStep
	txtStep->setValidator(inputRange);



	// on rempli le menu
	mnuContext->addAction(actwidPrecision);
	// on l'execute
	mnuContext->exec(event->globalPos()); 
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void QScienceSpinBox::stepCahnged()
///
/// \brief	(SLOT) When the step was changed by the user.
///
/// Change the step of this spinbox and hide the menu.
////////////////////////////////////////////////////////////////////////////////////////////////////
void QTechSpinBox::stepCahnged()
{
	mnuContext->hide();
	setStep(txtStep->text().toDouble());
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void QScienceSpinBox::setModeScientific()
///
/// \brief	(SLOT) When the user click on the Scientific mode menu.
///
/// Put postdigitsInt = postdigitsInt + predigitsInt, predigitsInt=1, and setUnitModifiers(false),
/// this show the value in a scientific notation by example: 0.000x10^00
////////////////////////////////////////////////////////////////////////////////////////////////////
void QTechSpinBox::setModeScientific(){
	actModeScientific->setChecked(true);
	predigitsInt = 1;
	postdigitsInt = postdigitsInt + predigitsClassicalInt;
	setUnitModifiers(false);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void QScienceSpinBox::setModeEngineer()
///
/// \brief	(SLOT) When the user click on the Engineer mode menu.
///
/// Put  predigitsInt=3, and setUnitModifiers(true),
/// this show the value in a engineering notation with a modifier for the unit
/// (..., n, µ, m, k, M, G ...) by example: 000.00 M.Unit
////////////////////////////////////////////////////////////////////////////////////////////////////
void QTechSpinBox::setModeEngineer(){
	actModeEngineer->setChecked(true);
	predigitsInt = 3;
	postdigitsInt = postdigitsClassicalInt;
	setUnitModifiers(true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void QScienceSpinBox::setModeClassical()
///
/// \brief	(SLOT) When the user click on the Classical mode menu.
///
/// come back to the first configuration for predigitsInt and postdigitsInt
/// and put setUnitModifiers(predigitsInt==3);
////////////////////////////////////////////////////////////////////////////////////////////////////
void QTechSpinBox::setModeClassical(){
	actModeEngineer->setChecked(true);
	predigitsInt = predigitsClassicalInt;
	postdigitsInt = postdigitsClassicalInt;
	setUnitModifiers(predigitsInt==3);

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void QScienceSpinBox::setupMenu()
///
/// \brief	(SLOT) Set up the context menu.
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void QTechSpinBox::setupMenu()
{
	//This function creates the standard context menu which is shown
	//when the user clicks on the text edit with the right mouse button. 
	mnuContext = lineEdit()->createStandardContextMenu();
	mnuContext->addSeparator();

	//The QActionGroup class groups all the mode actions together
	actModeGroup = new QActionGroup( this );

	//we create the mod action
	// Scientific : n.nnE+pp with n and p  numbers
	actModeScientific = new QAction(this);
	actModeScientific->setActionGroup(actModeGroup);
	actModeScientific->setText("Scientific");
	actModeScientific->setCheckable(true);
	actModeScientific->setChecked(true);

	//Engineer : from n.nnE+pp to nnn.nnE+pp with n and p  numbers and pp divided by 3
	actModeEngineer = new QAction(this);
	actModeEngineer->setActionGroup(actModeGroup);
	actModeEngineer->setText("Engineer");
	actModeEngineer->setCheckable(true);

	//Classical : 
	actModeClassical = new QAction(this);
	actModeClassical->setActionGroup(actModeGroup);
	actModeClassical->setText("Classical");
	actModeClassical->setCheckable(true);

	// we put all that in the context menu
	mnuMode = new QMenu(this);
	mnuMode->setTitle("Mode");
	mnuMode->addActions(actModeGroup->actions() );
	mnuContext->addMenu(mnuMode);

	// on construit le widget que l'on veut metre dans le menu
	actwidPrecision = new QWidgetAction(this);
	widStep = new QWidget(this);
	vlStep = new QVBoxLayout(widStep);
	lblStep = new QLabel(widStep);
	lblStep->setText("Step");

	txtStep = new QLineEdit(widStep);

	widStep->setLayout(vlStep);
	vlStep->addWidget(lblStep);
	vlStep->addWidget(txtStep);

	actwidPrecision->setDefaultWidget(widStep) ;

	// we connect the menus
	this->connect(actModeScientific, SIGNAL(triggered()), this, SLOT(setModeScientific()));
	this->connect(actModeEngineer, SIGNAL(triggered()), this, SLOT(setModeEngineer()));
	this->connect(actModeClassical, SIGNAL(triggered()), this, SLOT(setModeClassical()));
	this->connect(txtStep, SIGNAL(returnPressed()), this, SLOT(stepCahnged()));
	this->connect(txtStep, SIGNAL(	editingFinished()), this, SLOT(stepCahnged()));

}

void QTechSpinBox::setStep( double step )
{
	setSingleStep(step);
}
