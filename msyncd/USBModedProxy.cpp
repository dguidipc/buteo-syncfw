/*
 * This file is part of buteo-syncfw package
 *
 * Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 *
 * Contact: Sateesh Kavuri <sateesh.kavuri@nokia.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 */

#include <usb-moded/usb_moded-modes.h>
#include <usb-moded/usb_moded-dbus.h>
#include "USBModedProxy.h"
#include "LogMacros.h"

using namespace Buteo;

/*
 * Implementation of interface class USBModedProxy
 */

USBModedProxy::USBModedProxy(QObject *parent)
    : QDBusAbstractInterface(USB_MODE_SERVICE, USB_MODE_OBJECT, staticInterfaceName(), QDBusConnection::systemBus(), parent)
{
    FUNCTION_CALL_TRACE;
    if(false == QObject::connect(this, SIGNAL(sig_usb_state_ind(const QString&)), this, SLOT(slotModeChanged(const QString&))))
    {
        LOG_CRITICAL("Failed to connect to USB moded signal! USB notifications will not be available.");
    }
}

USBModedProxy::~USBModedProxy()
{
}

void USBModedProxy::slotModeChanged(const QString &mode)
{
    FUNCTION_CALL_TRACE;
    bool isConnected = false;
    
    if(MODE_OVI_SUITE == mode)
    {
        isConnected = true;
    }
    emit usbConnection(isConnected);
}

bool USBModedProxy::isUSBConnected()
{
    FUNCTION_CALL_TRACE;
    bool isConnected = false;

    QDBusPendingReply<QString> reply = this->mode_request();
    reply.waitForFinished();
    if(reply.isError())
    {
        LOG_CRITICAL("Get mode returns::" << reply.error());
    }
    else
    {
        LOG_INFO("USB connected in mode::" << reply.value());
        if(MODE_OVI_SUITE == reply.value())
        {
            isConnected = true;
        }
    }
    return isConnected;
}

