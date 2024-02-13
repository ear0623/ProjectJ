// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientComponent.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Common/TcpSocketBuilder.h"
#include "Serialization/ArrayWriter.h"




// Sets default values for this component's properties
UClientComponent::UClientComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UClientComponent::BeginPlay()
{
	Super::BeginPlay();

	//Connect();
	// ...
	MySocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(TEXT("Stream"), TEXT("ClientSocket"));

	FString Address = TEXT("127.0.0.1");
	FIPv4Address ip;
	FIPv4Address::Parse(Address, ip);

	int32 Port = 15689;
	TSharedRef<FInternetAddr>Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	Addr->SetIp(ip.Value);
	Addr->SetPort(Port);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Trying to connect.")));

	isConnected = MySocket->Connect(*Addr);

	if (isConnected)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("True")));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("False")));
	}
	FString Message = TEXT("ABCDE");
	TArray<uint8> MessageBytes;

	const TCHAR* MessageChars = Message.GetCharArray().GetData();
	// TCHAR 배열을 uint8 배열로 변환
	for (int32 i = 0; i < Message.Len(); ++i)
	{
		MessageBytes.Add(static_cast<uint8>(MessageChars[i]));
	}
	int32 BytesSend = 0;
	// Socket->Send() 함수를 호출하여 uint8 배열을 전송합니다.
	MySocket->Send(MessageBytes.GetData(), MessageBytes.Num(),BytesSend);
	Send(MySocket,MessageBytes.GetData(),1024 );
	
}


// Called every frame
void UClientComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



bool UClientComponent::Receive(FSocket* Socket, uint8* Results, int32 Size)
{
	int32 NumRead = 0;

	bool bSuccess = Socket->Recv(Results, Size, NumRead, ESocketReceiveFlags::Type::WaitAll);


	return bSuccess;
}

bool UClientComponent::Send(FSocket* Socket, const uint8* Buffer, int32 Size)
{
	int32 BytesSent = 0;
	
	bool bSuccess = Socket->Send(Buffer, Size, BytesSent);

	return bSuccess;
}

bool UClientComponent::SendPacket(FSocket* Socket, uint32 Type, const TArray<uint8>& Payload)
{
	return SendPacket(Socket, Type, Payload.GetData(), Payload.Num());
}

bool UClientComponent::SendPacket(FSocket* Socket, uint32 Type, const uint8* Payload, int32 PayloadSize)
{
	
	// make a header for the payload
	FMessageHeader Header(Type, PayloadSize);
	constexpr static int32 HeaderSize = sizeof(FMessageHeader);

	// serialize out the header
	FBufferArchive Ar;
	Ar << Header;
	int32 BytesSent = 1024;
	bool bSuccess = Socket->Send(Payload,HeaderSize,BytesSent);
	if (bSuccess)
	{
		UE_LOG(LogTemp, Log, TEXT("True"));
	}
	// append the payload bytes to send it in one network packet
	Ar.Append(Payload, PayloadSize);

	// Send it, and make sure it sent it all
	if (!Send(Socket, Ar.GetData(), Ar.Num()))
	{
		UE_LOG(LogSockets, Error, TEXT("Unable To Send."));
		return false;
	}
	return true;
}

bool UClientComponent::ReceivePacket(FSocket* Socket, TArray<uint8>& OutPayload)
{
	TArray<uint8> HeaderBuffer;
	int32 HeaderSize = sizeof(FMessageHeader);
	HeaderBuffer.AddZeroed(HeaderSize);

	// recv header
	int32 BytesRead = 0;
	if (!Receive(Socket, HeaderBuffer.GetData(), HeaderBuffer.Num()))
	{
		UE_LOG(LogTemp, Error, TEXT("Recv Header Failed."));
		return false;
	}

	FMessageHeader Header;
	{
		FMemoryReader Reader(HeaderBuffer);
		Reader << Header;
		UE_LOG(LogTemp, Log, TEXT("Recv Header Type : %d  Size : %d"), Header.Type, Header.Size);
	}

	int32 PayloadSize = Header.Size;
	OutPayload.SetNumZeroed(PayloadSize);

	if (Receive(Socket, OutPayload.GetData(), OutPayload.Num()))
	{
		return true;
	}

	return false;
}

void UClientComponent::Connect()
{
	MySocket = FTcpSocketBuilder(TEXT("ClientSocket"));

	FString IPAddress = TEXT("127.0.0.1");
	uint16 PortNumber = 15689;

	if (Connecter(MySocket, IPAddress, PortNumber))
	{
		UE_LOG(LogTemp, Log, TEXT("Socket Connected"));
		MySocket->SetNonBlocking(false);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Socket Connect Failed."));

		DestroySocket(MySocket);
	}
	
}

void UClientComponent::Disconnect()
{
	DestroySocket(MySocket);
}

void UClientComponent::Send(uint32 Type, const FString& Text)
{
	
	int32 BytesSent = 1024;
	FTCHARToUTF8 Convert(*Text);
	FArrayWriter WriterArray;
	WriterArray.Serialize((UTF8CHAR*)Convert.Get(), Convert.Length());
	if (SendPacket(MySocket, Type, WriterArray))
	{
		UE_LOG(LogTemp, Log, TEXT("Sent Text : %s  Size : %d"), *Text, WriterArray.Num());
		
	}
}

void UClientComponent::Recv()
{
	//
	// SCOPE_CYCLE_COUNTER(STAT_Recv);

	TArray<uint8> Payload;

	if (ReceivePacket(MySocket, Payload))
	{
		FString Data(Payload.Num(), (char*)Payload.GetData());
		UE_LOG(LogTemp, Log, TEXT("Recv data success.  data : %s  Payload : %d  size : %d"), *Data, Payload.Num(), Data.Len());
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Fail"));
	}
}

bool UClientComponent::Connecter(FSocket* Socket, FString IPAddress, int PortNumber)
{
	FIPv4Address IPAddr;
	if (!FIPv4Address::Parse(IPAddress, IPAddr))
	{
		UE_LOG(LogTemp, Error, TEXT("Ill-formed IP Address"));
		return false;
	}

	FIPv4Endpoint Endpoint = FIPv4Endpoint(IPAddr, PortNumber);

	if (Socket->Connect(*Endpoint.ToInternetAddr()))
	{
		if (Socket->GetConnectionState() == ESocketConnectionState::SCS_Connected)
		{
			return true;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SocketElse1-1"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ConnectElse"));
	}

	if (Socket->GetConnectionState() == ESocketConnectionState::SCS_Connected)
	{
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SocketElse1-2"));
	}

	FString ErrorText;
	PrintSocketError(ErrorText);

	UE_LOG(LogTemp, Error, TEXT("Socket Connect Failed.  Error : %s  ConnectionState : %d"),
		*ErrorText, (int32)Socket->GetConnectionState());
	return false;
}

void UClientComponent::PrintSocketError(FString& OutText)
{
	ESocketErrors Err = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLastErrorCode();
	const TCHAR* SocketErr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetSocketError(Err);
	OutText = SocketErr;
}

void UClientComponent::DestroySocket(FSocket* Socket)
{
	if (Socket)
	{
		if (Socket->GetConnectionState() == SCS_Connected)
		{
			Socket->Close();

			UE_LOG(LogTemp, Log, TEXT("Socket Closed."));
		}
	}
}

void UClientComponent::TestConeect()
{
	
		ISocketSubsystem* Socketsubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
		FSocket* ServerSocket = Socketsubsystem->CreateSocket(NAME_Stream, TEXT("serversocket"), false);
		if (!Socketsubsystem)
		{
			//subsystem
		}
		if (!ServerSocket)
		{
			//socket
		}
		FIPv4Address ServerIP(127, 0, 0, 1);

		TSharedRef<FInternetAddr> ServerAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
		ServerAddr->SetIp(ServerIP.Value);
		ServerAddr->SetPort(15689);

		bool Connected = ServerSocket->Connect(*ServerAddr);

		//TObjectPtr<FSocket> fSocket = FTcpSocketBuilder(TEXT("MyTCPClient")).AsReusable().BoundToAddress(ANY_ADDRESS)

		TArray<uint8> SendBuffer;
		TArray<uint8> ReciveBuffer;
		FTimespan WaitTime = FTimespan::FromSeconds(1);
		while (bIsRunning)
		{
			if (Connected)
			{
				int32 ByteSend = 0;
				ServerSocket->Send(SendBuffer.GetData(), SendBuffer.Num(), ByteSend);

				int32 ByteRecived = 0;
				if (ServerSocket->Wait(ESocketWaitConditions::WaitForRead, WaitTime))
				{
					ReciveBuffer.SetNumUninitialized(1024);
					ServerSocket->Recv(ReciveBuffer.GetData(), ReciveBuffer.Num(), ByteRecived);
				}
			}
			UE_LOG(LogTemp, Warning, TEXT("Client"));
			FPlatformProcess::Sleep(0.01f);
		}

		ServerSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ServerSocket);
	

}
