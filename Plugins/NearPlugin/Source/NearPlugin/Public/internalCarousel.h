#pragma once
 #include "gRPC_Base.h"

#include "GrpcBegin.h"

#include <protocol/internalCarousel.grpc.pb.h>
#include <protocol/mm.grpc.pb.h>

#include "GrpcEnd.h"

#include "mm.h"


#include "internalCarousel.generated.h"



UENUM(BlueprintType)
enum class FURequestCase : uint8
{	
	Default UMETA(DisplayName = "Default"),
	kNewPlayer UMETA(DisplayName = "kNewPlayer"),
	kNewRoom UMETA(DisplayName = "kNewRoom"),
	kRemovePlayer UMETA(DisplayName = "kRemovePlayer"),
	kRoomFinished UMETA(DisplayName = "kRoomFinished"),
	kAcceptGame UMETA(DisplayName = "kAcceptGame")
};

UENUM(BlueprintType)
enum class FUResponseCase : uint8
{	
	Default UMETA(DisplayName = "Default"),
	kRoomReady UMETA(DisplayName = "kRoomReady"),
	kNewRoomPlayer UMETA(DisplayName = "kNewRoomPlayer"),
	kNeedUsersAccept UMETA(DisplayName = "kNeedUsersAccept"),
	kRoomNotFound UMETA(DisplayName = "kRoomNotFound"),
	kAcceptingCanceled UMETA(DisplayName = "kAcceptingCanceled"),
	kPlayerInQueue UMETA(DisplayName = "kPlayerInQueue"),
	kPlayerInBattle UMETA(DisplayName = "kPlayerInBattle"),
	kPlayerOutOfLine UMETA(DisplayName = "kPlayerOutOfLine")
};



USTRUCT(BlueprintType)
struct FUNeedUsersAccept 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalCarouselProto")
	TArray<FString> user_ids;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalCarouselProto")
	bool manual_accept;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalCarouselProto")
	int32 time_to_accept;

	FUNeedUsersAccept& operator=(const game::battlemon::carousel::internal::NeedUsersAccept& grpcNeedUsersAccept);

};


USTRUCT(BlueprintType)
struct FUInternalPlayer 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalCarouselProto")
	FString user_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalCarouselProto")
	FString lemon_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalCarouselProto")
	FString room_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalCarouselProto")
	FUGameMode mode;

	FUInternalPlayer& operator=(const game::battlemon::carousel::internal::InternalPlayer& grpcInternalPlayer);

};


USTRUCT(BlueprintType)
struct FUInternalRoomInfo 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalCarouselProto")
	FString room_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalCarouselProto")
	FUGameMode mode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalCarouselProto")
	TArray<FUInternalPlayer> players;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalCarouselProto")
	FURegion region;

	FUInternalRoomInfo& operator=(const game::battlemon::carousel::internal::InternalRoomInfo& grpcInternalRoomInfo);

};


USTRUCT(BlueprintType)
struct FUCarouselResponses 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalCarouselProto")
	FUResponseCase response_case;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalCarouselProto")
	FUInternalRoomInfo room_ready;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalCarouselProto")
	FUInternalPlayer new_room_player;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalCarouselProto")
	FUNeedUsersAccept need_users_accept;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalCarouselProto")
	FUInternalPlayer room_not_found;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalCarouselProto")
	FUInternalRoomInfo accepting_canceled;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalCarouselProto")
	FUInternalPlayer player_in_queue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalCarouselProto")
	FUInternalPlayer player_in_battle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalCarouselProto")
	FUInternalPlayer player_out_of_line;

	FUCarouselResponses& operator=(const game::battlemon::carousel::internal::CarouselResponses& grpcCarouselResponses);

};


USTRUCT(BlueprintType)
struct FUCarouselRequests 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalCarouselProto")
	FURequestCase request_case;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalCarouselProto")
	FUInternalPlayer new_player;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalCarouselProto")
	FUInternalRoomInfo new_room;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalCarouselProto")
	FUInternalPlayer remove_player;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalCarouselProto")
	FUInternalRoomInfo room_finished;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalCarouselProto")
	FUInternalPlayer accept_game;

	FUCarouselRequests& operator=(const game::battlemon::carousel::internal::CarouselRequests& grpcCarouselRequests);

};


FURequestCase& operator<<(FURequestCase &UE, const game::battlemon::carousel::internal::CarouselRequests::RequestCase& grpc);

FUResponseCase& operator<<(FUResponseCase &UE, const game::battlemon::carousel::internal::CarouselResponses::ResponseCase& grpc);

game::battlemon::carousel::internal::CarouselRequests::RequestCase& operator<<(game::battlemon::carousel::internal::CarouselRequests::RequestCase & grpc, const FURequestCase &UE); 

game::battlemon::carousel::internal::CarouselResponses::ResponseCase& operator<<(game::battlemon::carousel::internal::CarouselResponses::ResponseCase & grpc, const FUResponseCase &UE); 

game::battlemon::carousel::internal::NeedUsersAccept &operator<<(game::battlemon::carousel::internal::NeedUsersAccept &grpcNeedUsersAccept, const FUNeedUsersAccept &UE);

game::battlemon::carousel::internal::InternalPlayer &operator<<(game::battlemon::carousel::internal::InternalPlayer &grpcInternalPlayer, const FUInternalPlayer &UE);

game::battlemon::carousel::internal::InternalRoomInfo &operator<<(game::battlemon::carousel::internal::InternalRoomInfo &grpcInternalRoomInfo, const FUInternalRoomInfo &UE);

game::battlemon::carousel::internal::CarouselResponses &operator<<(game::battlemon::carousel::internal::CarouselResponses &grpcCarouselResponses, const FUCarouselResponses &UE);

game::battlemon::carousel::internal::CarouselRequests &operator<<(game::battlemon::carousel::internal::CarouselRequests &grpcCarouselRequests, const FUCarouselRequests &UE);

