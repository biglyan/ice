// **********************************************************************
//
// Copyright (c) 2003-2017 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICESSL_SECURE_TRANSPORT_TRANSCEIVER_I_H
#define ICESSL_SECURE_TRANSPORT_TRANSCEIVER_I_H

#include <IceSSL/Config.h>
#include <IceSSL/InstanceF.h>
#include <IceSSL/SSLEngineF.h>
#include <IceSSL/Plugin.h>

#include <Ice/Transceiver.h>
#include <Ice/UniqueRef.h>
#include <Ice/Network.h>

#ifdef ICE_USE_SECURE_TRANSPORT

#include <Security/Security.h>
#include <Security/SecureTransport.h>
#include <CoreFoundation/CoreFoundation.h>

namespace IceSSL
{

class ConnectorI;
class AcceptorI;

class TransceiverI : public IceInternal::Transceiver
{
public:

    virtual IceInternal::NativeInfoPtr getNativeInfo();

    virtual IceInternal::SocketOperation initialize(IceInternal::Buffer&, IceInternal::Buffer&);
    virtual IceInternal::SocketOperation closing(bool, const Ice::LocalException&);
    virtual void close();
    virtual IceInternal::SocketOperation write(IceInternal::Buffer&);
    virtual IceInternal::SocketOperation read(IceInternal::Buffer&);

    virtual std::string protocol() const;
    virtual std::string toString() const;
    virtual std::string toDetailedString() const;
    virtual Ice::ConnectionInfoPtr getInfo() const;
    virtual void checkSendSize(const IceInternal::Buffer&);
    virtual void setBufferSize(int rcvSize, int sndSize);

    OSStatus writeRaw(const char*, size_t*) const;
    OSStatus readRaw(char*, size_t*) const;

private:

    TransceiverI(const InstancePtr&, const IceInternal::TransceiverPtr&, const std::string&, bool);
    virtual ~TransceiverI();

    friend class ConnectorI;
    friend class AcceptorI;

    const InstancePtr _instance;
    const SecureTransportEnginePtr _engine;
    const std::string _host;
    const std::string _adapterName;
    const bool _incoming;
    const IceInternal::TransceiverPtr _delegate;

    IceInternal::UniqueRef<SSLContextRef> _ssl;
    IceInternal::UniqueRef<SecTrustRef> _trust;
    bool _connected;

    enum SSLWantFlags
    {
        SSLWantRead = 0x1,
        SSLWantWrite = 0x2
    };

    mutable Ice::Byte _flags;
    size_t _maxSendPacketSize;
    size_t _maxRecvPacketSize;
    std::string _cipher;
    std::vector<std::string> _certs;
    bool _verified;
    std::vector<CertificatePtr> _nativeCerts;
    size_t _buffered;
};
typedef IceUtil::Handle<TransceiverI> TransceiverIPtr;

}

#endif

#endif
