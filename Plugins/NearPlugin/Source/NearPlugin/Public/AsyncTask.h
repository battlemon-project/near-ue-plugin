// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Async/AsyncWork.h"

#include "gRPC_Base.h"

/**
 * 
 */

template <typename StructResult, typename Service, typename grpcRequest, typename grpcResponse>
class FMAsyncTask :public FNonAbandonableTask
{
	friend class FAsyncTask<FMAsyncTask>;

    FStructResultDelegate* structResultDelegate;
    Service* service;
    StructResult* result;
    grpcRequest* request;
    grpcResponse(Service::*CallRPC)(grpcRequest* _request);
    grpcResponse(Service::* CallRPCvoid)();

public:
    FMAsyncTask() :result(nullptr), request(new grpcRequest()), CallRPC(nullptr){};
    ~FMAsyncTask() { delete request; request = nullptr; };
    void SetData(Service* _service, FStructResultDelegate* _structResultDelegate, StructResult* _result, grpcResponse(Service::*_CallRPC)())
    {
        service = _service;
        structResultDelegate = _structResultDelegate;
        result = _result;
        CallRPCvoid = _CallRPC;
    };

    void SetData(Service* _service, FStructResultDelegate* _structResultDelegate, StructResult* _result, grpcRequest* _request, grpcResponse(Service::* _CallRPC)(grpcRequest* _request))
    {
        service = _service;
        structResultDelegate = _structResultDelegate;
        result = _result;
        *request = *_request;
        CallRPC = _CallRPC;
    };

    void GetData(StructResult* _result)
    {
        _result = result;
    };

protected:
    void DoWork()
    {
        if (service != nullptr)
        {
            if(request != nullptr)
                *result = (service->*CallRPC)(request);
            else
                *result = (service->*CallRPCvoid)();
            if (structResultDelegate->IsBound())
                structResultDelegate->Broadcast();
        }
    }

    FORCEINLINE TStatId GetStatId() const
    {
        RETURN_QUICK_DECLARE_CYCLE_STAT(FMAsyncTask, STATGROUP_ThreadPoolAsyncTasks);
    }
};