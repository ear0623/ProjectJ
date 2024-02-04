// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SqlConnectComponent.h"
#include "MySqlPlugin/Public/include/jdbc/mysql_connection.h"
#include "MySqlPlugin/Public/include/jdbc/cppconn/exception.h"
#include "MySqlPlugin/Public/include/jdbc/cppconn/resultset.h"
#include "MySqlPlugin/Public/include/jdbc/cppconn/statement.h"
#include "MySqlPlugin/Public/include/jdbc/cppconn/prepared_statement.h"
//#include "MySqlPlugin/Public/include/jdbc/cppconn/driver.h"



// Sets default values for this component's properties
USqlConnectComponent::USqlConnectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USqlConnectComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USqlConnectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USqlConnectComponent::ConnectSQL()
{
	sql::Driver* Driver = nullptr;
	sql::Connection* Connection = nullptr;
	sql::Statement* State = nullptr;
	sql::ResultSet* Resultset = nullptr;
	sql::PreparedStatement* PreparedStatement = nullptr;

	try
	{
		//Driver = get_driver_instance();
		//Connection = Driver->
	}
	catch (const std::exception&)
	{

	}

}

