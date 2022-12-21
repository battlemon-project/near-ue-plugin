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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalUpdatesProto")
	TArray<FString> near_ids;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalUpdatesProto")
	FString message;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalUpdatesProto")
	bool remove_on_fail;

	FUInternalUpdate& operator=(const game::battlemon::updates::InternalUpdate& grpcInternalUpdate);

};


game::battlemon::updates::InternalUpdate &operator<<(game::battlemon::updates::InternalUpdate &grpcInternalUpdate, const FUInternalUpdate &UE);

