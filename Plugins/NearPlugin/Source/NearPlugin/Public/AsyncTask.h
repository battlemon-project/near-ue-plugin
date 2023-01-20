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

    grpc::ClientContext* context;
    Service* service;
    StructResult* result;
    grpcRequest* request;
    grpcResponse(Service::*CallRPC)(grpc::ClientContext* _context, const grpcRequest* _request);
    grpcResponse(Service::* CallRPCvoid)(grpc::ClientContext* _context);

public:
    FMAsyncTask() :context(new grpc::ClientContext), result(nullptr), request(new grpcRequest()), CallRPC(nullptr){};
    ~FMAsyncTask() 
    {
        if (request != nullptr)
        {
            delete request;
            request = nullptr;
        }
        if (context != nullptr)
        {
            delete context;
            context = nullptr;
        }
    };
    void SetData(Service* _service, StructResult* _result, TMap<FString, FString>& _context, grpcResponse(Service::*_CallRPC)(grpc::ClientContext* _context))
    {
        if (_context.Num() != 0)
        {
            for (auto& Elem : _context)
                context->AddMetadata(CONV_FSTRING_TO_CHAR(Elem.Key), CONV_FSTRING_TO_CHAR(Elem.Value));
        }
        service = _service;
        result = _result;
        CallRPCvoid = _CallRPC;
    };

    void SetData(Service* _service, StructResult* _result, grpcRequest* _request, TMap<FString, FString>& _context, grpcResponse(Service::* _CallRPC)(grpc::ClientContext* _context, const grpcRequest* _request))
    {
        if (_context.Num() != 0)
        {
            for (auto& Elem : _context)
                context->AddMetadata(CONV_FSTRING_TO_CHAR(Elem.Key), CONV_FSTRING_TO_CHAR(Elem.Value));
        }
        service = _service;
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
            if(CallRPC != nullptr)
                *result = (service->*CallRPC)(context, request);
            else
                *result = (service->*CallRPCvoid)(context);
        }
    }

    FORCEINLINE TStatId GetStatId() const
    {
        RETURN_QUICK_DECLARE_CYCLE_STAT(FMAsyncTask, STATGROUP_ThreadPoolAsyncTasks);
    }
};