
#1. 确定CMake的最低版本需求
CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)

#2. 确定工程名
PROJECT(TraderCTPMini LANGUAGES CXX)
SET(CMAKE_CXX_STANDARD 11)


IF (WIN32)
	IF("${CMAKE_GENERATOR}" MATCHES "(Win64|IA64)")
		SET(INCS $ENV{MyX64Deps12}/include)
		SET(LNKS $ENV{MyX64Deps12}/lib)
	ELSE()
		SET(INCS $ENV{MyDepends12}/include)
		SET(LNKS $ENV{MyDepends12}/lib)
	ENDIF()
ELSE (UNIX)
	SET (MyDeps "/home/mydeps")
	SET(INCS ${MyDeps}/include)
	SET(LNKS ${MyDeps}/lib)
ENDIF ()

SET(SRC  
	${PROJECT_SOURCE_DIR}/TraderCTPMini.cpp
	${PROJECT_SOURCE_DIR}/TraderCTPMini.h
	
	${PROJECT_SOURCE_DIR}/ThostTraderApi/ThostFtdcTraderApi.h
	${PROJECT_SOURCE_DIR}/ThostTraderApi/ThostFtdcUserApiDataType.h
	${PROJECT_SOURCE_DIR}/ThostTraderApi/ThostFtdcUserApiStruct.h
)
SET(LNKS "${LNKS} ${PROJECT_SOURCE_DIR}/ThostTraderApi")

SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../build/bin)

INCLUDE_DIRECTORIES(${INCS})
LINK_DIRECTORIES(${LNKS})
ADD_LIBRARY(TraderCTPMini SHARED ${SRC})

IF (WIN32)
ELSE (UNIX)
	SET_TARGET_PROPERTIES(TraderCTPMini PROPERTIES
		CXX_VISIBILITY_PRESET hidden
		C_VISIBILITY_PRESET hidden
		VISIBILITY_INLINES_HIDDEN 1)
ENDIF ()

