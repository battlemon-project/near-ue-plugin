#pragma once
 #include "gRPC_Base.h"

#include "GrpcBegin.h"

#include <protocol/updates.grpc.pb.h>
#include <protocol/common.grpc.pb.h>
#include <protocol/items.grpc.pb.h>

#include "GrpcEnd.h"

#include "common.h"
#include "items.h"


#include "updates.generated.h"



UENUM(BlueprintType)
enum class FUUpdateCase : uint8
{	
	Default UMETA(DisplayName = "Default"),
	kRoomNeedAccept UMETA(DisplayName = "kRoomNeedAccept"),
	kRoomAcceptingCanceled UMETA(DisplayName = "kRoomAcceptingCanceled"),
	kRoomFound UMETA(DisplayName = "kRoomFound"),
	kRoomTeammates UMETA(DisplayName = "kRoomTeammates"),
	kRoomReady UMETA(DisplayName = "kRoomReady"),
	kUserIsAlreadyInLine UMETA(DisplayName = "kUserIsAlreadyInLine"),
	kUserIsAlreadyInBattle UMETA(DisplayName = "kUserIsAlreadyInBattle"),
	kUserOutOfLine UMETA(DisplayName = "kUserOutOfLine")
};



USTRUCT(BlueprintType)
struct FURoomPlayer 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | updatesProto")
	FString user_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | updatesProto")
	FUItem lemon;

	FURoomPlayer& operator=(const game::battlemon::updates::RoomPlayer& grpcRoomPlayer);

};


USTRUCT(BlueprintType)
struct FURoomInfo 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | updatesProto")
	FString room_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | updatesProto")
	FString server_ip;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | updatesProto")
	TArray<FURoomPlayer> players;

	FURoomInfo& operator=(const game::battlemon::updates::RoomInfo& grpcRoomInfo);

};


USTRUCT(BlueprintType)
struct FURoomNeedAccept 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | updatesProto")
	bool manual_accept;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | updatesProto")
	int32 time_to_accept;

	FURoomNeedAccept& operator=(const game::battlemon::updates::RoomNeedAccept& grpcRoomNeedAccept);

};


USTRUCT(BlueprintType)
struct FUUpdateMessage 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | updatesProto")
	FUUpdateCase update_case;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | updatesProto")
	FURoomNeedAccept room_need_accept;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | updatesProto")
	FUEmpty room_accepting_canceled;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | updatesProto")
	FURoomInfo room_found;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | updatesProto")
	FURoomInfo room_teammates;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | updatesProto")
	FURoomInfo room_ready;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | updatesProto")
	FUEmpty user_is_already_in_line;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | updatesProto")
	FURoomInfo user_is_already_in_battle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | updatesProto")
	FUEmpty user_out_of_line;

	FUUpdateMessage& operator=(const game::battlemon::updates::UpdateMessage& grpcUpdateMessage);

};


USTRUCT(BlueprintType)
struct FUUpdate 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | updatesProto")
	FString id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | updatesProto")
	int64 timestamp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | updatesProto")
	FString message;

	FUUpdate& operator=(const game::battlemon::updates::Update& grpcUpdate);

};


FUUpdateCase& operator<<(FUUpdateCase &UE, const game::battlemon::updates::UpdateMessage::UpdateCase& grpc);

game::battlemon::updates::UpdateMessage::UpdateCase& operator<<(game::battlemon::updates::UpdateMessage::UpdateCase & grpc, const FUUpdateCase &UE); 

game::battlemon::updates::RoomPlayer &operator<<(game::battlemon::updates::RoomPlayer &grpcRoomPlayer, const FURoomPlayer &UE);

game::battlemon::updates::RoomInfo &operator<<(game::battlemon::updates::RoomInfo &grpcRoomInfo, const FURoomInfo &UE);

game::battlemon::updates::RoomNeedAccept &operator<<(game::battlemon::updates::RoomNeedAccept &grpcRoomNeedAccept, const FURoomNeedAccept &UE);

game::battlemon::updates::UpdateMessage &operator<<(game::battlemon::updates::UpdateMessage &grpcUpdateMessage, const FUUpdateMessage &UE);

game::battlemon::updates::Update &operator<<(game::battlemon::updates::Update &grpcUpdate, const FUUpdate &UE);

