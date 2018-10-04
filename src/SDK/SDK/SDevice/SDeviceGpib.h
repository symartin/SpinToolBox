////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	SDevice\SDeviceGpib.h
//
// summary:	Declares the device gpib class
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SDEVICEGPIB_H_
#define SDEVICEGPIB_H_

#include "SDeviceVirtual.h"
#include "../SInterface/SInterfaceGpib.h"

#include "../gpib-32/ni488.h"

#include <QString>
#include <QObject>
#include <QScriptable>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SDeviceGpib
///
/// \brief	class for all the GPIB devices. 
///
/// \author	Sylvain Martin
/// \date	1/13/2011
/// 		
/// \ingroup SDeviceMod
////////////////////////////////////////////////////////////////////////////////////////////////////

class SDeviceGpib: public SDeviceVirtual {
Q_OBJECT;
public:
	
	SDeviceGpib(QObject *parent=0) : SDeviceVirtual(parent),  available_(false){}; //< constructeur Qt de QObject


public :
	SInterfaceGpib* GpibInterface () const;
	

	virtual SInterfaceGpib::GpibElement GpibElement() const ;
	virtual void setGpibElement(const SInterfaceGpib::GpibElement elmt);

	Q_INVOKABLE virtual Addr4882_t PAD() const;
	Q_INVOKABLE virtual void setPAD(const Addr4882_t pad);

	Q_INVOKABLE virtual void gpibSend(QString commande);
	Q_INVOKABLE virtual QVariant gpibRead(const long buffer = 131072); //131072L correspond a 128Ko

	Q_INVOKABLE virtual void enableLocal();


	Q_INVOKABLE virtual QString name(void) const;
	Q_INVOKABLE void setUnavailable(void);
	Q_INVOKABLE void delay(double i) ;

signals:
	void logError(QString log);
	void logEvent(QString log);

protected:
	SInterfaceGpib::GpibElement elmt_; ///< contains the name, the primary and secondary address
	SInterfaceGpib * gpib_; ///< pointeur to the GPIB board
	bool available_;
};

#endif /* SDEVICEGPIB_H_ */
