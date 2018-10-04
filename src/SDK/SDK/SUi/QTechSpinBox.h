#ifndef QTECHSPINBOX_H
#define QTECHSPINBOX_H

#include <QtGui/qabstractspinbox.h>
#ifdef QT_PLUGIN
#include <QtDesigner/QDesignerExportWidget>
#endif

#include <QtGui>
#include <QtCore>


class
#ifdef QT_PLUGIN
      QDESIGNER_WIDGET_EXPORT
#endif
      QTechSpinBox : public QAbstractSpinBox {
   Q_OBJECT

   Q_ENUMS(Roundingrule)
   Q_PROPERTY(unsigned int predigits READ predigits WRITE setPredigits)
   Q_PROPERTY(unsigned int postdigits READ postdigits WRITE setPostdigits)
   Q_PROPERTY(double minimum READ minimum WRITE setMinimum)
   Q_PROPERTY(double maximum READ maximum WRITE setMaximum)
   Q_PROPERTY(double singleStep READ singleStep WRITE setSingleStep)
   Q_PROPERTY(QString baseUnit READ baseUnit WRITE setBaseUnit)
   Q_PROPERTY(Roundingrule roundingRule READ roundingRule WRITE setRoundingRule)
   Q_PROPERTY(double value READ value WRITE setValue)
   Q_PROPERTY(bool unitModifiers READ unitModifiers WRITE setUnitModifiers)
   Q_PROPERTY(bool stepInUnit READ stepInUnit WRITE setStepInUnit)

public:
   enum Roundingrule {Cut, BankersRule, Arithmetic, Symmetric};
   explicit QTechSpinBox(QWidget *parent = 0);
   double value() const {return d_value;}

   double singleStep() const {return singleStepDbl;}
   void setSingleStep(const double &singlestep);

   unsigned short int predigits() const {return predigitsInt;}
   void setPredigits(const unsigned short int &predigits);
   unsigned short int postdigits() const {return postdigitsInt;}
   void setPostdigits(const unsigned short int &postdigits);
   QString baseUnit() const {return baseunitString;}
   void setBaseUnit(const QString &baseunit);

   double minimum() const {return d_minimum;}
   void setMinimum(double min);
   double maximum() const {return d_maximum;}
   void setMaximum(double max);

   Roundingrule roundingRule() const {return roundingruleEnum;}
   void setRoundingRule(const Roundingrule& roundingrule);

   bool unitModifiers() const {return unitmodifiersBool;}
   void setUnitModifiers(bool useModifiers);

   bool stepInUnit();
   void setStepInUnit(bool b);
   
   virtual double valueFromText(const QString &text) const;
   virtual QString textFromValue(double val) const;
   virtual void fixup(QString &str) const;
   virtual QValidator::State validate(QString &input, int &pos) const;

public slots:
   void setValue(double val);
   void contextMenuEvent(QContextMenuEvent *event);
   void setStep(double step);

protected slots:
   void setValueFromText();

private slots:
	   void stepCahnged();
	   void setModeScientific();
	   void setModeEngineer();
	   void setModeClassical();

signals:
   void valueChanged(double);
   void valueChanged(const QString &);

protected:
   virtual void stepBy (int steps);
   virtual StepEnabled stepEnabled() const;
   void setRegExpValidator();
   void updateDisplay();
   bool isNumeric(QChar oneChar) const;

private:
	void setupMenu();

   bool unitmodifiersBool;
   double d_minimum;
   double d_maximum;
   double d_value;
   double singleStepDbl;   // **factor** for multiplication or division
   QString baseunitString;
   unsigned short int postdigitsInt;
    unsigned short int postdigitsClassicalInt; // qd on passe en represntation scientifique ou Engineer
   unsigned short int predigitsInt;
   unsigned short int predigitsClassicalInt; // qd on passe en represntation scientifique ou Engineer


   Roundingrule roundingruleEnum;
   bool stepInUnitBool;

   // pour le menu contextuel
   QMenu * mnuContext;
   QWidget * widStep;
   QVBoxLayout * vlStep;
   QLabel * lblStep;
   QLineEdit * txtStep;
   QWidgetAction  * actwidPrecision;

   QMenu * mnuMode;
   QAction * actModeScientific;
   QAction * actModeEngineer;
   QAction * actModeClassical;
   QActionGroup* actModeGroup;
};

#endif // QTECHSPINBOX_H
