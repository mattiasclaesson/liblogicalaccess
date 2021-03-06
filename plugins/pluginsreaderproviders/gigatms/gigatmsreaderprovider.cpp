/**
 * \file gigatmsreaderprovider.cpp
 * \author Maxime C. <maxime-dev@islog.com>
 * \brief GIGA-TMS reader provider.
 */

#include "gigatmsreaderprovider.hpp"
#include "logicalaccess/readerproviders/serialportdatatransport.hpp"
#include "logicalaccess/myexception.hpp"

#ifdef __unix__
#include <stdlib.h>
#include <sys/time.h>
#endif

#include <sstream>
#include <iomanip>

#include "gigatmsreaderunit.hpp"

namespace logicalaccess
{
	GigaTMSReaderProvider::GigaTMSReaderProvider() :
        ReaderProvider()
    {
    }

    std::shared_ptr<GigaTMSReaderProvider> GigaTMSReaderProvider::getSingletonInstance()
    {
        static std::shared_ptr<GigaTMSReaderProvider> instance;
        if (!instance)
        {
            instance.reset(new GigaTMSReaderProvider());
            instance->refreshReaderList();
        }

        return instance;
    }

	GigaTMSReaderProvider::~GigaTMSReaderProvider()
    {
        release();
    }

    void GigaTMSReaderProvider::release()
    {
    }

    std::shared_ptr<ReaderUnit> GigaTMSReaderProvider::createReaderUnit()
    {
        LOG(LogLevel::INFOS) << "Creating new reader unit with empty port... (Serial port auto-detect will be used when connecting to reader)";

        std::shared_ptr<GigaTMSReaderUnit> ret(new GigaTMSReaderUnit());
        ret->setReaderProvider(std::weak_ptr<ReaderProvider>(shared_from_this()));

        return ret;
    }

    bool GigaTMSReaderProvider::refreshReaderList()
    {
        d_readers.clear();

        std::vector<std::shared_ptr<SerialPortXml> > ports;
        EXCEPTION_ASSERT_WITH_LOG(SerialPortXml::EnumerateUsingCreateFile(ports), LibLogicalAccessException, "Can't enumerate the serial port list.");

        for (std::vector<std::shared_ptr<SerialPortXml> >::iterator i = ports.begin(); i != ports.end(); ++i)
        {
            std::shared_ptr<GigaTMSReaderUnit> unit(new GigaTMSReaderUnit());
            std::shared_ptr<SerialPortDataTransport> dataTransport = std::dynamic_pointer_cast<SerialPortDataTransport>(unit->getDataTransport());
            dataTransport->setSerialPort(*i);
            unit->setReaderProvider(std::weak_ptr<ReaderProvider>(shared_from_this()));
            d_readers.push_back(unit);
        }

        return true;
    }
}