/*
 * RouterConfigurationPort.hh
 *
 *  Created on: Nov 12, 2012
 *      Author: yuasa
 */

#ifndef ROUTERCONFIGURATIONPORT_HH_
#define ROUTERCONFIGURATIONPORT_HH_

#include "CxxUtilities/CxxUtilities.hh"

class RouterConfigurationPortException: public CxxUtilities::Exception {
public:
	RouterConfigurationPortException(int status) :
			CxxUtilities::Exception(status) {

	}

public:
	virtual ~RouterConfigurationPortException() {
	}

public:
	std::string toString() {
		std::string str;
		switch (status) {
		case NotImplemented:
			str = "NotImplemented";
			break;
		case OperationFailed:
			str="OperationFailed";
			break;
		case InvalidPortNumber:
			str = "InvalidPortNumber";
			break;
		case InvalidLinkFrequency:
			str = "InvalidLinkFrequency";
			break;
		case RMAPInitiatorIsNotAvailable:
			str = "RMAPInitiatorIsNotAvailable";
			break;
		}
		return str;
	}
public:
	enum {
		NotImplemented, //
		OperationFailed, //
		InvalidPortNumber, //
		InvalidLinkFrequency, //
		RMAPInitiatorIsNotAvailable
	};
};

class RouterConfigurationPort {
protected:
	std::vector<uint8_t> additionalTargetSpaceWireAddress;
	std::vector<uint8_t> additionalReplyAddress;

protected:
	RMAPInitiator* rmapInitiator;

public:
	virtual ~RouterConfigurationPort() {
	}

public:
	virtual RMAPTargetNode* getRMAPTargetNodeInstance() = 0;

public:
	virtual size_t getTotalNumberOfPorts() = 0;

public:
	virtual size_t getNumberOfExternalPorts() = 0;

public:
	virtual size_t getNumberOfInternalPorts() = 0;

public:
	virtual uint32_t getRoutingTableAddress(uint8_t logicalAddress) throw (RouterConfigurationPortException) = 0;

public:
	virtual RMAPMemoryObject* getRoutingTableMemoryObject(uint8_t logicalAddress)
			throw (RouterConfigurationPortException) = 0;

public:
	virtual uint32_t getLinkFrequencyRegisterAddress(uint8_t port) throw (RouterConfigurationPortException) = 0;

public:
	virtual RMAPMemoryObject* getLinkFrequencyRegisterMemoryObject(uint8_t port)
			throw (RouterConfigurationPortException) = 0;

public:
	virtual std::vector<double> getAvailableLinkFrequencies(uint8_t port) = 0;

public:
	virtual void setLinkFrequency(uint8_t port, double linkFrequency) throw (RouterConfigurationPortException,RMAPInitiatorException) = 0;

public:
	virtual void setLinkEnable(uint8_t port) throw (RouterConfigurationPortException,RMAPInitiatorException) = 0;

public:
	virtual void unsetLinkEnable(uint8_t port) throw (RouterConfigurationPortException,RMAPInitiatorException) = 0;

public:
	virtual bool isLinkEnabled(uint8_t port) throw (RouterConfigurationPortException,RMAPInitiatorException) = 0;

public:
	virtual void setLinkStart(uint8_t port) throw (RouterConfigurationPortException,RMAPInitiatorException) = 0;

public:
	virtual void unsetLinkStart(uint8_t port) throw (RouterConfigurationPortException,RMAPInitiatorException) = 0;

public:
	virtual bool isLinkStarted(uint8_t port) throw (RouterConfigurationPortException,RMAPInitiatorException) = 0;

public:
	virtual void setAutoStart(uint8_t port) throw (RouterConfigurationPortException,RMAPInitiatorException) = 0;

public:
	virtual void unsetAutoStart(uint8_t port) throw (RouterConfigurationPortException,RMAPInitiatorException) = 0;

public:
	virtual bool isAutoStarted(uint8_t port) throw (RouterConfigurationPortException,RMAPInitiatorException) = 0;

public:
	bool isLinkFrequencyValid(uint8_t port, double linkFrequency) {
		std::vector<double> linkFrequencies = getAvailableLinkFrequencies(port);
		for (size_t i = 0; i < linkFrequencies.size(); i++) {
			if (linkFrequencies[i] == linkFrequency) {
				return true;
			}
		}
		return false;
	}

public:
	const std::vector<uint8_t>& getAdditionalReplyAddress() const {
		return additionalReplyAddress;
	}

public:
	void setAdditionalReplyAddress(std::vector<uint8_t>& additionalReplyAddress) {
		this->additionalReplyAddress = additionalReplyAddress;
	}

public:
	const std::vector<uint8_t>& getAdditionalTargetSpaceWireAddress() const {
		return additionalTargetSpaceWireAddress;
	}

public:
	void setAdditionalTargetSpaceWireAddress(std::vector<uint8_t>& additionalTargetSpaceWireAddress) {
		this->additionalTargetSpaceWireAddress = additionalTargetSpaceWireAddress;
	}

public:
	RMAPInitiator* getRMAPInitiator() const {
		return rmapInitiator;
	}

public:
	void setRMAPInitiator(RMAPInitiator* rmapInitiator) {
		this->rmapInitiator = rmapInitiator;
	}
};

#endif /* ROUTERCONFIGURATIONPORT_HH_ */