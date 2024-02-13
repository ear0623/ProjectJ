#include <WinSock2.h>
#include <windows.h>
#include <process.h>
#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include "jdbc/cppconn/driver.h"
#include "jdbc/cppconn/exception.h"
#include "jdbc/cppconn/resultset.h"
#include "jdbc/cppconn/statement.h"
#include "jdbc/cppconn/prepared_statement.h"

#pragma comment(lib,"ws2_32")
#pragma comment(lib,"debug/mysqlcppconn")

#include <Windows.h>

#define SAFE_DELETE(p)        if (p) { delete (p);     (p) = 0; }


void SQLConnect();

std::string Utf8ToMultiByte(std::string utf8_str)
{
	if (utf8_str.length() == 0)
	{
		return "";
	}
	std::string resultString; char* pszIn = new char[utf8_str.length() + 1];
	strncpy_s(pszIn, utf8_str.length() + 1, utf8_str.c_str(), utf8_str.length());
	int nLenOfUni = 0, nLenOfANSI = 0; wchar_t* uni_wchar = NULL;
	char* pszOut = NULL;
	// 1. utf8 Length
	if ((nLenOfUni = MultiByteToWideChar(CP_UTF8, 0, pszIn, (int)strlen(pszIn), NULL, 0)) <= 0)
		return nullptr;
	uni_wchar = new wchar_t[nLenOfUni + 1];
	memset(uni_wchar, 0x00, sizeof(wchar_t) * (nLenOfUni + 1));
	// 2. utf8 --> unicode
	nLenOfUni = MultiByteToWideChar(CP_UTF8, 0, pszIn, (int)strlen(pszIn), uni_wchar, nLenOfUni);
	// 3. ANSI(multibyte) Length
	if ((nLenOfANSI = WideCharToMultiByte(CP_ACP, 0, uni_wchar, nLenOfUni, NULL, 0, NULL, NULL)) <= 0)
	{
		delete[] uni_wchar; return 0;
	}
	pszOut = new char[nLenOfANSI + 1];
	memset(pszOut, 0x00, sizeof(char) * (nLenOfANSI + 1));
	// 4. unicode --> ANSI(multibyte)
	nLenOfANSI = WideCharToMultiByte(CP_ACP, 0, uni_wchar, nLenOfUni, pszOut, nLenOfANSI, NULL, NULL);
	pszOut[nLenOfANSI] = 0;
	resultString = pszOut;
	delete[] uni_wchar;
	delete[] pszOut;
	return resultString;
}

/*
* @brief window���� ����ϴ� ANSI ���ڵ��� ������ ����ϴ� utf-8 ���ڵ� ���ڵ����� ���� �մϴ�.
*/
std::string MultiByteToUtf8(std::string multibyte_str)
{
	if (multibyte_str.length() == 0)
	{
		return "";
	}

	char* pszIn = new char[multibyte_str.length() + 1];
	strncpy_s(pszIn, multibyte_str.length() + 1, multibyte_str.c_str(), multibyte_str.length());

	std::string resultString;

	int nLenOfUni = 0, nLenOfUTF = 0;
	wchar_t* uni_wchar = NULL;
	char* pszOut = NULL;

	// 1. ANSI(multibyte) Length
	if ((nLenOfUni = MultiByteToWideChar(CP_ACP, 0, pszIn, (int)strlen(pszIn), NULL, 0)) <= 0)
		return 0;

	uni_wchar = new wchar_t[nLenOfUni + 1];
	memset(uni_wchar, 0x00, sizeof(wchar_t) * (nLenOfUni + 1));

	// 2. ANSI(multibyte) ---> unicode
	nLenOfUni = MultiByteToWideChar(CP_ACP, 0, pszIn, (int)strlen(pszIn), uni_wchar, nLenOfUni);

	// 3. utf8 Length
	if ((nLenOfUTF = WideCharToMultiByte(CP_UTF8, 0, uni_wchar, nLenOfUni, NULL, 0, NULL, NULL)) <= 0)
	{
		delete[] uni_wchar;
		return 0;
	}

	pszOut = new char[nLenOfUTF + 1];
	memset(pszOut, 0, sizeof(char) * (nLenOfUTF + 1));

	// 4. unicode ---> utf8
	nLenOfUTF = WideCharToMultiByte(CP_UTF8, 0, uni_wchar, nLenOfUni, pszOut, nLenOfUTF, NULL, NULL);
	pszOut[nLenOfUTF] = 0;
	resultString = pszOut;

	delete[] uni_wchar;
	delete[] pszOut;

	return resultString;
}

void SQLConnect()
{
	//workbench
	sql::Driver* Driver = nullptr;
	sql::Connection* Connection = nullptr; //�ּ�
	sql::Statement* statement = nullptr; //SQL //�ϵ��ڵ�
	sql::ResultSet* resultSet = nullptr; //���
	sql::PreparedStatement* preparedStatement = nullptr; //sql + �� �߰�

	try
	{

		Driver = get_driver_instance();//open

		Connection = Driver->connect("tcp://127.0.0.1", "root", "1234");//

		//use world
		Connection->setSchema("guest_book");

		statement = Connection->createStatement();

		preparedStatement = Connection->prepareStatement("insert into geustbook (`writer`, `memo`) value (?, ?)");
		//preparedStatement = Connection->prepareStatement("insert into geustbook('writer','memo') value(?,?)");
		preparedStatement->setString(1, "sh.choi2");
		preparedStatement->setString(2, MultiByteToUtf8("ŸŸ"));

		preparedStatement->execute();

		resultSet = statement->executeQuery("select * from geustbook order by idx desc;");

		//statement->execute("insert into guestbook('writer','memo' value('ȫ�ٹ�','��')");//sql injection -> preparestatement�� ������

		for (; resultSet->next();)
		{
			std::cout << resultSet->getInt("idx") << ": "
				<< Utf8ToMultiByte(resultSet->getString("writer")) << ":"
				<< Utf8ToMultiByte(resultSet->getString("memo")) << ":"
				<< Utf8ToMultiByte(resultSet->getString("reg_date")) << std::endl;
		}

		Connection = Driver->connect("tcp://127.0.0.1", "root", "1234");
		if (Connection == nullptr)
		{
			exit(-1);
		}
		Connection->setSchema("guest_book");

		statement = Connection->createStatement();
		resultSet = statement->executeQuery("select *from my_guest_book");

		preparedStatement = Connection->prepareStatement("INSERT INTO my_guest_book(name,region,number) VALUES(?,?,?)");

		/*preparedStatement->setString(1, MultiByteToUtf8(Buffer));
		preparedStatement->setString(2, MultiByteToUtf8(Buffer1));
		preparedStatement->setInt(3, Number);*/

		preparedStatement->execute();

		resultSet = statement->executeQuery("select * from my_guest_book order by idx desc;");

		for (; resultSet->next();)
		{
			std::cout << resultSet->getInt("idx") << " : "
				<< Utf8ToMultiByte(resultSet->getString("name")) << " : "
				<< Utf8ToMultiByte(resultSet->getString("region")) << " : "
				<< resultSet->getInt("number") << std::endl;
		}

		//name 5byte regin 8byte number 12byte

	}
	catch (const sql::SQLException e)
	{
		std::cout << e.what();
	}
	catch (std::exception e)
	{

	}

	SAFE_DELETE(Connection);
	SAFE_DELETE(statement);
	SAFE_DELETE(resultSet);
	SAFE_DELETE(preparedStatement);

}

int main()
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN ListenSockAddr;
	memset(&ListenSockAddr, 0, sizeof(ListenSockAddr));
	ListenSockAddr.sin_family = AF_INET;
	ListenSockAddr.sin_addr.s_addr = INADDR_ANY;//�ϴ�
	ListenSockAddr.sin_port = htons(15689);
	if (ListenSocket == INVALID_SOCKET)
	{
		std::cout << "-1" << std::endl;
		return 1;
	}


	int bindresult= bind(ListenSocket, (SOCKADDR*)&ListenSockAddr, sizeof(ListenSockAddr));
	if (bindresult > 0)
	{

	}
	else
	{
		std::cout << "NotBind " << bindresult << std::endl;
	}

	int ListenResult = listen(ListenSocket, 5);
	if (ListenResult > 0)
	{
		std::cout << "ListenSucess" << std::endl;
	}
	if (ListenResult <= 0)
	{
		std::cout << "NotListen "<<ListenResult << std::endl;
		std::cout << WSAGetLastError() << std::endl;
	
	}
	// �޴� ����

	SOCKADDR_IN ClientSocketAddr;
	memset(&ClientSocketAddr, 0, sizeof(ClientSocketAddr));
	int ClientSockAddrSize = sizeof(ListenSockAddr);
	SOCKET ClientSocket = accept(ListenSocket, (SOCKADDR*)&ClientSocketAddr, &ClientSockAddrSize);
	if (ClientSocket)
	{
		std::cout << "Socket.isvalid" << std::endl;
	
	}
	else
	{
		std::cout << "Socket.Not" << std::endl;
	}
	//accept ����
	char SendBuffer[1024] = { 0, };
	char RecvBuffer[1024] = { 0, };
	while (true)
	{
		
		//recive����
		int RecvLength =recv(ClientSocket, RecvBuffer, sizeof(RecvBuffer),0);
		std::cout << RecvLength << std::endl;
		if (RecvLength<0)
		{
			std::cout << "-1" << std::endl;
			break;
		}
		if (RecvLength == 0)
		{
			std::cout << "0" << std::endl;
			break;
		}
		if (RecvLength > 0)
		{
			std::cout << "1" << std::endl;
			std::cout << "Received: " << RecvLength << std::endl;
			int SendBuuferLength = sizeof(RecvLength);
			int SendLength = send(ClientSocket, SendBuffer,SendBuuferLength, 0);
			std::cout << "Send:" << SendLength << std::endl;
		}
	}
	

	//HANDLE ThreadHandle = (HANDLE)_beginthreadex(0,)


	closesocket(ListenSocket);
	closesocket(ClientSocket);
	WSACleanup();
	return 0;
}

