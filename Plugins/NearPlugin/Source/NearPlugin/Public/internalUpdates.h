#pragma once
 #include "gRPC_Base.h"

#include "GrpcBegin.h"

#include <protocol/internalUpdates.grpc.pb.h>

#include "GrpcEnd.h"



#include "internalUpdates.generated.h"





USTRUCT(BlueprintType)
struct FUInternalUpdate 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalUpdatesProto")
	TArray<FString> user_ids;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalUpdatesProto")
	FString message;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalUpdatesProto")
	bool remove_on_fail;

	FUInternalUpdate& operator=(const game::battlemon::updates::InternalUpdate& grpcInternalUpdate);

};


game::battlemon::updates::InternalUpdate &operator<<(game::battlemon::updates::InternalUpdate &grpcInternalUpdate, const FUInternalUpdate &UE);

