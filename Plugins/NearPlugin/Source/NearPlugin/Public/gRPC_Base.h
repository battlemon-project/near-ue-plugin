// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GrpcBegin.h"

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#include <string>



#if PLATFORM_WINDOWS
#include <wincrypt.h>
#include <Windows.h>
#include <cryptuiapi.h>


#endif // PLATFORM_WINDOWS

#ifdef UE_BUILD_DEVELOPMENT
#include <stdio.h>
#include <stdarg.h>
#endif

#if defined(__unix__)
#include <uchar.h>
#endif

#include "GrpcEnd.h"

#include "UObject/Object.h"
#include "Async/AsyncWork.h"
#include "Runtime/Core/Public/Async/ParallelFor.h"

#include "gRPC_Base.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStructResultDelegate);

#if defined(__unix__)

//#define CONV_FSTRING_TO_CHAR(str) U16toString(str)
//#define CONV_CHAR_TO_FSTRING(str)  StringtoU16(str)
#define CONV_FSTRING_TO_CHAR(str) TCHAR_TO_UTF8(*str)
#define CONV_CHAR_TO_FSTRING(str)  UTF8_TO_TCHAR(str)

static inline std::string U16toString(const FString& wstr)
{
	int32 size = wstr.Len();
	std::string str = "";
	str.resize(size + 1);
	
	char cstr[3] = "\0";
	mbstate_t mbs;
	const char16_t* chr16 = *wstr;

	ParallelFor(size, [&](int32 Idx)
		{
			memset(&mbs, 0, sizeof(mbs));
			memmove(cstr, "\0\0\0", 3);
			c16rtomb(cstr, chr16[Idx], &mbs);
			str[Idx] = *std::string(cstr).c_str();
		});

	str[size] = '\0';
	return str;
}

static inline FString StringtoU16(const std::string& str)
{
	int32 size = str.size();
	std::u16string wstr = u"";
	wstr.resize(size);

	char16_t c16str[3] = u"\0";
	mbstate_t mbs;
	const char* chr = str.c_str();

	ParallelFor(size, [&](int32 Idx)
		{
			memset(&mbs, 0, sizeof(mbs));
			memmove(c16str, u"\0\0\0", 3);
			mbrtoc16(c16str, &chr[Idx], 3, &mbs);
			wstr[Idx] = *std::u16string(c16str).c_str();
		});

	FString strUe(wstr.c_str());
	return strUe;
}
#define UE_LOG_REQUEST(Format, ...) ((void)0)
#else
#define CONV_FSTRING_TO_CHAR(str) TCHAR_TO_ANSI(*str)
#define CONV_CHAR_TO_FSTRING(str) FString(str)

#if defined(UE_BUILD_DEVELOPMENT)
#pragma warning (disable : 4840)
static inline void printLOG(std::string format, ...)
{
	va_list ptrIn;
	int iT;
	const char* cPtr;
	std::string str;

	FString res = "";

	va_start(ptrIn, format);
	for (const char* c = format.c_str(); *c; c++)
	{
		if (*c != '%')
		{
			res += *c;
			continue;
		}
		else
		{
			switch (*++c)
			{
			case 'i':
				iT = va_arg(ptrIn, int);
				res += FString::FromInt(iT);
				break;
			case 's':
				str = va_arg(ptrIn, std::string);
				res += CONV_CHAR_TO_FSTRING(str.c_str());
				break;
			case 'c':
				cPtr = va_arg(ptrIn, const char*);
				res += CONV_CHAR_TO_FSTRING(cPtr);
				break;
			}
		}

	}
	va_end(ptrIn);

	UE_LOG(LogTemp, Display, TEXT("%s"), *res);
};
#define UE_LOG_REQUEST(Format, ...) printLOG(Format, ##__VA_ARGS__);
#endif
#endif


#define CREATE_ASINCTASK(StructResult, Service, grpcRequest, grpcResponse) FAsyncTask<FMAsyncTask<StructResult, Service, grpcRequest, grpcResponse>>* Task = new FAsyncTask<FMAsyncTask<StructResult, Service, grpcRequest, grpcResponse>>()
#define GET_ASINCTASK Task
#define CAST_ASINCTASK(StructResult, Service, grpcRequest, grpcResponse) static_cast<FAsyncTask<FMAsyncTask<StructResult, Service, grpcRequest, grpcResponse>>*>


class gRPC_SSL
{
#ifdef WIN32
	std::string utf8Encode(const std::wstring& wstr)
	{
		if (wstr.empty())
			return std::string();

		int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
		std::string strTo(sizeNeeded, 0);
		WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], sizeNeeded, NULL, NULL);
		return strTo;
	}

public:
	grpc::SslCredentialsOptions getSslOptions()
	{
		grpc::SslCredentialsOptions result;

		HANDLE hRootCertStore = CertOpenSystemStoreW(NULL, L"ROOT");
		if (!hRootCertStore)
			return result;

		PCCERT_CONTEXT pCert = NULL;
		while ((pCert = CertEnumCertificatesInStore(hRootCertStore, pCert)) != NULL)
		{
			DWORD size = 0;
			CryptBinaryToStringW(pCert->pbCertEncoded, pCert->cbCertEncoded, CRYPT_STRING_BASE64HEADER, NULL, &size);
			std::vector<WCHAR> pem(size);
			CryptBinaryToStringW(pCert->pbCertEncoded, pCert->cbCertEncoded, CRYPT_STRING_BASE64HEADER, pem.data(), &size);

			result.pem_root_certs += utf8Encode(pem.data());
		}
		CertCloseStore(hRootCertStore, 0);

		return result;
	}
#else
public:
	grpc::SslCredentialsOptions getSslOptions()
	{
		return grpc::SslCredentialsOptions();
	}
#endif

	~gRPC_SSL() {};
};


template <typename Service, typename ServiceStub>
class gRPC_Stub : public gRPC_SSL
{
	void SetError(const grpc::Status& status)
	{
		error = FString("Code: ") + FString::FromInt(static_cast<int>(status.error_code()));
		error += FString(" --- >>>>ErrorMessage: ") + CONV_CHAR_TO_FSTRING(status.error_message().c_str());
		UE_LOG(LogTemp, Error, TEXT("CallGRPC error %s"), *error);
	}

protected:
	std::unique_ptr<ServiceStub> stub;
	FString error;
	void* got_tag;

	void CreateContext(grpc::ClientContext& context, TArray<FString> meta_key, TArray<FString> meta_value, const int number)
	{
		for (size_t i = 0; i < number; i++)
		{
			context.AddMetadata(CONV_FSTRING_TO_CHAR(meta_key[i]), CONV_FSTRING_TO_CHAR(meta_value[i]));
		}
	}
	void CreateContext(grpc::ClientContext& context, std::string meta_key[], std::string meta_value[], const int number)
	{
		for (size_t i = 0; i < number; i++)
		{
			context.AddMetadata(meta_key[i], meta_value[i]);
		}
	}

public:
	void* Task;
	gRPC_Stub(const bool& ssl, FString& url) : Task(nullptr)
	{
		error = "";
		if (ssl)
			stub = std::unique_ptr<ServiceStub>(Service::NewStub((grpc::CreateChannel(CONV_FSTRING_TO_CHAR(url), grpc::SslCredentials(getSslOptions())))));
		else
			stub = std::unique_ptr<ServiceStub>(Service::NewStub((grpc::CreateChannel(CONV_FSTRING_TO_CHAR(url), grpc::InsecureChannelCredentials()))));
	}

	virtual ~gRPC_Stub() {};

	bool CheckError(grpc::Status status)
	{
		if (status.ok())
		{
			return true;
		}

		SetError(status);
		return false;
	}


	FString& GetError()
	{
		return error;
	}
};
/**
 * 
 */

USTRUCT()
struct FWTF
{
	GENERATED_BODY()
};

