cmake_minimum_required(VERSION 3.23...3.27)
project(libtao LANGUAGES CXX)

include(GNUInstallDirs)

if(NOT "${_TAO_CMAKE_DIR}" IN_LIST CMAKE_MODULE_PATH)
  list(APPEND CMAKE_MODULE_PATH "${_TAO_CMAKE_DIR}")
endif()
include(tao_idl)

set(TAO_INCLUDE_DIR "${TAO_SOURCE_DIR}" CACHE INTERNAL "")

add_library(TAO
  Abstract_Servant_Base.cpp
  Acceptor_Filter.cpp
  Acceptor_Registry.cpp
  Adapter.cpp
  Adapter_Factory.cpp
  Adapter_Registry.cpp
  AnyTypeCode_Adapter.cpp
  Argument.cpp
  Asynch_Queued_Message.cpp
  Asynch_Reply_Dispatcher_Base.cpp
  Base_Transport_Property.cpp
  BiDir_Adapter.cpp
  Bind_Dispatcher_Guard.cpp
  Block_Flushing_Strategy.cpp
  Blocked_Connect_Strategy.cpp
  CDR.cpp
  Cleanup_Func_Registry.cpp
  Client_Strategy_Factory.cpp
  ClientRequestInterceptor_Adapter.cpp
  ClientRequestInterceptor_Adapter_Factory.cpp
  Codeset_Manager.cpp
  Codeset_Manager_Factory_Base.cpp
  Codeset_Translator_Base.cpp
  Collocated_Invocation.cpp
  Collocation_Resolver.cpp
  Connect_Strategy.cpp
  Connection_Handler.cpp
  Connection_Purging_Strategy.cpp
  Connector_Registry.cpp
  CORBA_String.cpp
  CORBALOC_Parser.cpp
  CORBANAME_Parser.cpp
  debug.cpp
  default_client.cpp
  Default_Collocation_Resolver.cpp
  Default_Endpoint_Selector_Factory.cpp
  default_resource.cpp
  default_server.cpp
  Default_Stub_Factory.cpp
  Default_Thread_Lane_Resources_Manager.cpp
  DLL_Parser.cpp
  Dynamic_Adapter.cpp
  Endpoint.cpp
  Endpoint_Selector_Factory.cpp
  Environment.cpp
  Exception.cpp
  Exclusive_TMS.cpp
  Fault_Tolerance_Service.cpp
  FILE_Parser.cpp
  Flushing_Strategy.cpp
  GIOP_Fragmentation_Strategy.cpp
  GIOP_Message_Base.cpp
  GIOP_Message_Generator_Parser.cpp
  GIOP_Message_Generator_Parser_10.cpp
  GIOP_Message_Generator_Parser_11.cpp
  GIOP_Message_Generator_Parser_12.cpp
  GIOP_Message_Generator_Parser_Impl.cpp
  GIOP_Message_Locate_Header.cpp
  GIOP_Message_State.cpp
  GIOP_Message_Version.cpp
  GUIResource_Factory.cpp
  HR_Time_Policy_Strategy.cpp
  HTTP_Client.cpp
  HTTP_Handler.cpp
  HTTP_Parser.cpp
  IFR_Client_Adapter.cpp
  IIOP_Acceptor.cpp
  IIOP_Connection_Handler.cpp
  IIOP_Connector.cpp
  IIOP_Endpoint.cpp
  IIOP_Factory.cpp
  IIOP_Profile.cpp
  IIOP_Transport.cpp
  Incoming_Message_Queue.cpp
  Incoming_Message_Stack.cpp
  Invocation_Adapter.cpp
  Invocation_Base.cpp
  Invocation_Endpoint_Selectors.cpp
  Invocation_Retry_Params.cpp
  Invocation_Retry_State.cpp
  IOR_Parser.cpp
  IORInterceptor_Adapter.cpp
  IORInterceptor_Adapter_Factory.cpp
  Leader_Follower.cpp
  Leader_Follower_Flushing_Strategy.cpp
  LF_CH_Event.cpp
  LF_Connect_Strategy.cpp
  LF_Event.cpp
  LF_Event_Binder.cpp
  LF_Event_Loop_Thread_Helper.cpp
  LF_Follower.cpp
  LF_Follower_Auto_Adder.cpp
  LF_Follower_Auto_Ptr.cpp
  LF_Invocation_Event.cpp
  LF_Multi_Event.cpp
  LF_Strategy.cpp
  LF_Strategy_Complete.cpp
  LocalObject.cpp
  LocateRequest_Invocation.cpp
  LocateRequest_Invocation_Adapter.cpp
  LRU_Connection_Purging_Strategy.cpp
  MCAST_Parser.cpp
  MMAP_Allocator.cpp
  MProfile.cpp
  Muxed_TMS.cpp
  Network_Priority_Protocols_Hooks.cpp
  New_Leader_Generator.cpp
  Null_Fragmentation_Strategy.cpp
  NVList_Adapter.cpp
  Object.cpp
  Object_KeyC.cpp
  Object_Loader.cpp
  Object_Proxy_Broker.cpp
  Object_Ref_Table.cpp
  ObjectKey_Table.cpp
  On_Demand_Fragmentation_Strategy.cpp
  operation_details.cpp
  ORB.cpp
  ORB_Core.cpp
  ORB_Core_Auto_Ptr.cpp
  ORB_Core_TSS_Resources.cpp
  ORB_Table.cpp
  ORB_Time_Policy.cpp
  ORBInitializer_Registry.cpp
  ORBInitializer_Registry_Adapter.cpp
  params.cpp
  Parser_Registry.cpp
  Pluggable_Messaging_Utils.cpp
  Policy_Current.cpp
  Policy_Current_Impl.cpp
  Policy_Manager.cpp
  Policy_Set.cpp
  Policy_Validator.cpp
  PolicyFactory_Registry_Adapter.cpp
  PolicyFactory_Registry_Factory.cpp
  Principal.cpp
  Profile.cpp
  Profile_Transport_Resolver.cpp
  Protocol_Factory.cpp
  Protocols_Hooks.cpp
  Queued_Data.cpp
  Queued_Message.cpp
  Reactive_Connect_Strategy.cpp
  Reactive_Flushing_Strategy.cpp
  Refcounted_ObjectKey.cpp
  Remote_Invocation.cpp
  Remote_Object_Proxy_Broker.cpp
  Reply_Dispatcher.cpp
  Request_Dispatcher.cpp
  RequestInterceptor_Adapter.cpp
  Resource_Factory.cpp
  Resume_Handle.cpp
  Server_Strategy_Factory.cpp
  ServerRequestInterceptor_Adapter.cpp
  ServerRequestInterceptor_Adapter_Factory.cpp
  Service_Callbacks.cpp
  Service_Context.cpp
  Service_Context_Handler.cpp
  Service_Context_Handler_Registry.cpp
  Services_Activate.cpp
  Storable_Base.cpp
  Storable_Factory.cpp
  Storable_File_Guard.cpp
  Storable_FlatFileStream.cpp
  String_Alloc.cpp
  Stub.cpp
  Stub_Factory.cpp
  Synch_Invocation.cpp
  Synch_Queued_Message.cpp
  Synch_Reply_Dispatcher.cpp
  System_Time_Policy_Strategy.cpp
  SystemException.cpp
  Tagged_Components.cpp
  Tagged_Profile.cpp
  TAO_Internal.cpp
  TAO_Server_Request.cpp
  TAO_Singleton_Manager.cpp
  target_specification.cpp
  Thread_Lane_Resources.cpp
  Thread_Lane_Resources_Manager.cpp
  Thread_Per_Connection_Handler.cpp
  Time_Policy_Manager.cpp
  Transport.cpp
  Transport_Acceptor.cpp
  Transport_Connector.cpp
  Transport_Descriptor_Interface.cpp
  Transport_Mux_Strategy.cpp
  Transport_Queueing_Strategies.cpp
  Transport_Selection_Guard.cpp
  Transport_Timer.cpp
  TSS_Resources.cpp
  Typecode_typesC.cpp
  TypeCodeFactory_Adapter.cpp
  UserException.cpp
  Valuetype_Adapter.cpp
  Valuetype_Adapter_Factory.cpp
  Wait_On_Leader_Follower.cpp
  Wait_On_LF_No_Upcall.cpp
  Wait_On_Reactor.cpp
  Wait_On_Read.cpp
  Wait_Strategy.cpp
  WrongTransactionC.cpp
  ZIOP_Adapter.cpp

  # AnyTypeCode CPP ===========================================================
  # AnyTypeCode/Alias_TypeCode.cpp
  AnyTypeCode/Alias_TypeCode_Static.cpp
  AnyTypeCode/Any.cpp
  # AnyTypeCode/Any_Array_Impl_T.cpp
  AnyTypeCode/Any_Basic_Impl.cpp
  # AnyTypeCode/Any_Basic_Impl_T.cpp
  # AnyTypeCode/Any_Dual_Impl_T.cpp
  AnyTypeCode/Any_Impl.cpp
  # AnyTypeCode/Any_Impl_T.cpp
  # AnyTypeCode/Any_Special_Impl_T.cpp
  AnyTypeCode/Any_SystemException.cpp
  AnyTypeCode/Any_Unknown_IDL_Type.cpp
  AnyTypeCode/AnyTypeCode_Adapter_Impl.cpp
  AnyTypeCode/append.cpp
  AnyTypeCode/BasicTypeTraits.cpp
  AnyTypeCode/Empty_Param_TypeCode.cpp
  # AnyTypeCode/Enum_TypeCode.cpp
  AnyTypeCode/Enum_TypeCode_Static.cpp
  AnyTypeCode/ExceptionA.cpp
  # AnyTypeCode/Fixed_TypeCode.cpp
  AnyTypeCode/Indirected_Type_TypeCode.cpp
  AnyTypeCode/Marshal.cpp
  AnyTypeCode/NVList.cpp
  AnyTypeCode/NVList_Adapter_Impl.cpp
  # AnyTypeCode/Objref_TypeCode.cpp
  AnyTypeCode/Objref_TypeCode_Static.cpp
  # AnyTypeCode/Recursive_Type_TypeCode.cpp
  # AnyTypeCode/Sequence_TypeCode.cpp
  AnyTypeCode/Sequence_TypeCode_Static.cpp
  AnyTypeCode/skip.cpp
  # AnyTypeCode/String_TypeCode.cpp
  AnyTypeCode/String_TypeCode_Static.cpp
  # AnyTypeCode/Struct_TypeCode.cpp
  AnyTypeCode/Struct_TypeCode_Static.cpp
  AnyTypeCode/SystemExceptionA.cpp
  AnyTypeCode/True_RefCount_Policy.cpp
  AnyTypeCode/TypeCode.cpp
  # AnyTypeCode/TypeCode_Base_Attributes.cpp
  # AnyTypeCode/TypeCode_Case_Base_T.cpp
  # AnyTypeCode/TypeCode_Case_Enum_T.cpp
  # AnyTypeCode/TypeCode_Case_T.cpp
  AnyTypeCode/TypeCode_CDR_Extraction.cpp
  AnyTypeCode/TypeCode_Constants.cpp
  AnyTypeCode/TypeCodeA.cpp
  # AnyTypeCode/Union_TypeCode.cpp
  AnyTypeCode/Union_TypeCode_Static.cpp
  # AnyTypeCode/Value_TypeCode.cpp
  AnyTypeCode/Value_TypeCode_Static.cpp
  AnyTypeCode/WrongTransactionA.cpp

  # PortableServer CPP ========================================================
  PortableServer/Acceptor_Filter_Factory.cpp
  PortableServer/Active_Object_Map.cpp
  PortableServer/Active_Object_Map_Entry.cpp
  PortableServer/Active_Policy_Strategies.cpp
  # PortableServer/Basic_SArgument_T.cpp
  # PortableServer/BD_String_SArgument_T.cpp
  PortableServer/Collocated_Arguments_Converter.cpp
  PortableServer/Collocated_Object_Proxy_Broker.cpp
  PortableServer/Creation_Time.cpp
  PortableServer/Default_Acceptor_Filter.cpp
  PortableServer/Default_Policy_Validator.cpp
  PortableServer/Default_Servant_Dispatcher.cpp
  PortableServer/Direct_Collocation_Upcall_Wrapper.cpp
  # PortableServer/Fixed_Array_SArgument_T.cpp
  # PortableServer/Fixed_Size_SArgument_T.cpp
  PortableServer/IdAssignmentPolicy.cpp
  PortableServer/IdAssignmentStrategy.cpp
  PortableServer/IdAssignmentStrategySystem.cpp
  PortableServer/IdAssignmentStrategyUser.cpp
  PortableServer/IdUniquenessPolicy.cpp
  PortableServer/IdUniquenessStrategy.cpp
  PortableServer/IdUniquenessStrategyMultiple.cpp
  PortableServer/IdUniquenessStrategyUnique.cpp
  PortableServer/ImplicitActivationPolicy.cpp
  PortableServer/ImplicitActivationStrategyExplicit.cpp
  PortableServer/ImplicitActivationStrategyImplicit.cpp
  PortableServer/ImR_Client_Adapter.cpp
  PortableServer/Key_Adapters.cpp
  PortableServer/LifespanPolicy.cpp
  PortableServer/LifespanStrategy.cpp
  PortableServer/LifespanStrategyPersistent.cpp
  PortableServer/LifespanStrategyTransient.cpp
  PortableServer/Network_Priority_Hook.cpp
  PortableServer/Non_Servant_Upcall.cpp
  PortableServer/Object_Adapter.cpp
  PortableServer/Object_Adapter_Factory.cpp
  # PortableServer/Object_SArgument_T.cpp
  PortableServer/Operation_Table_Binary_Search.cpp
  PortableServer/Operation_Table.cpp
  PortableServer/Operation_Table_Dynamic_Hash.cpp
  PortableServer/Operation_Table_Linear_Search.cpp
  PortableServer/Operation_Table_Perfect_Hash.cpp
  PortableServer/ORT_Adapter_Factory.cpp
  PortableServer/POA_Cached_Policies.cpp
  PortableServer/POA_Current.cpp
  PortableServer/POA_Current_Factory.cpp
  PortableServer/POA_Current_Impl.cpp
  PortableServer/POA_Guard.cpp
  PortableServer/POAManager.cpp
  PortableServer/POAManagerFactory.cpp
  PortableServer/POA_Policy_Set.cpp
  PortableServer/PortableServer.cpp
  PortableServer/PortableServer_Functions.cpp
  PortableServer/PortableServer_WFunctions.cpp
  PortableServer/PS_ForwardA.cpp
  PortableServer/PS_ForwardC.cpp
  PortableServer/Regular_POA.cpp
  PortableServer/RequestProcessingPolicy.cpp
  PortableServer/RequestProcessingStrategyAOMOnly.cpp
  PortableServer/RequestProcessingStrategy.cpp
  PortableServer/RequestProcessingStrategyDefaultServant.cpp
  PortableServer/RequestProcessingStrategyServantActivator.cpp
  PortableServer/RequestProcessingStrategyServantLocator.cpp
  PortableServer/RequestProcessingStrategyServantManager.cpp
  PortableServer/Root_POA.cpp
  PortableServer/Servant_Base.cpp
  PortableServer/Servant_Dispatcher.cpp
  PortableServer/ServantRetentionPolicy.cpp
  PortableServer/ServantRetentionStrategy.cpp
  PortableServer/ServantRetentionStrategyNonRetain.cpp
  PortableServer/ServantRetentionStrategyRetain.cpp
  PortableServer/Servant_Upcall.cpp
  # PortableServer/Servant_var.cpp
  # PortableServer/Special_Basic_SArgument_T.cpp
  PortableServer/StrategyFactory.cpp
  PortableServer/SUpcall_commands.cpp
  PortableServer/ThreadPolicy.cpp
  PortableServer/ThreadStrategyORBControl.cpp
  PortableServer/ThreadStrategySingle.cpp
  # PortableServer/UB_String_SArgument_T.cpp
  PortableServer/Upcall_Command.cpp
  PortableServer/Upcall_Wrapper.cpp
  # PortableServer/Var_Array_SArgument_T.cpp
  # PortableServer/Var_Size_SArgument_T.cpp
  # PortableServer/Vector_SArgument_T.cpp
)
add_library(TAO::TAO ALIAS TAO)
target_link_libraries(TAO PUBLIC ACE)

set(common
  TAO
  INCLUDE_BASE "${TAO_SOURCE_DIR}"
  IDL_FLAGS -GA -Gp -Gd -oA tao/AnyTypeCode
)
_tao_idl(${common} -SS -Sorb IDL_FILES GIOP.pidl IOP.pidl)
_tao_idl(${common} -SS -Sorb -Sci
  IDL_FILES
    CONV_FRAME.pidl
    Current.pidl
    IIOP.pidl
    IIOP_Endpoints.pidl
    IOP.pidl
    Messaging_PolicyValue.pidl
    Messaging_SyncScope.pidl
    ObjectIdList.pidl
    orb_types.pidl
    Policy_Manager.pidl
    Policy_Current.pidl
    PI_Forward.pidl
    PortableInterceptor.pidl
    Services.pidl
    TAO.pidl
    TimeBase.pidl
)
_tao_idl(${common} -SS -Sorb -Sci -Sa IDL_FILES Policy_Forward.pidl)
_tao_idl(${common} -SS -Sorb -Sci -Sat IDL_FILES ParameterMode.pidl)
_tao_idl(${common} -SS -Sorb -Sci -Gse -Gata
  IDL_FILES
    BooleanSeq.pidl
    CharSeq.pidl
    DoubleSeq.pidl
    FloatSeq.pidl
    LongDoubleSeq.pidl
    LongLongSeq.pidl
    LongSeq.pidl
    OctetSeq.pidl
    ShortSeq.pidl
    StringSeq.pidl
    ULongLongSeq.pidl
    ULongSeq.pidl
    UShortSeq.pidl
    WCharSeq.pidl
    WStringSeq.pidl
)
_tao_idl(${common} -SS -Sorb -Sci -Gse -Gata --idl-version 4 IDL_FILES Int8Seq.pidl UInt8Seq.pidl)
_tao_idl(${common} -GT -oS tao/PortableServer -Gd
  # -Wb,include_guard=TAO_PORTABLESERVER_SAFE_INCLUDE
  # -Wb,safe_include=tao/PortableServer/PortableServer.h
  # BUILD_SEPARATE
  IDL_FILES Policy.pidl
)

# AnyTypeCode IDL =============================================================
set(common
  TAO
  INCLUDE_BASE "${TAO_SOURCE_DIR}"
  IDL_FLAGS -Gp -Gd -Sci -SS -GA -iC tao/AnyTypeCode
)
_tao_idl(${common} -Sorb
  IDL_FILES
    AnyTypeCode/AnySeq.pidl
    AnyTypeCode/Dynamic_Parameter.pidl
    AnyTypeCode/ValueModifier.pidl
    AnyTypeCode/Visibility.pidl
    AnyTypeCode/Dynamic.pidl
)
_tao_idl(${common} IDL_FILES AnyTypeCode/Bounds.pidl)

_tao_idl(${common} -Sorb
  IDL_FILES
    AnyTypeCode/AnySeq.pidl
    AnyTypeCode/Dynamic_Parameter.pidl
    AnyTypeCode/ValueModifier.pidl
    AnyTypeCode/Visibility.pidl
    AnyTypeCode/Dynamic.pidl
)
_tao_idl(${common} IDL_FILES AnyTypeCode/Bounds.pidl)

# PortableServer IDL ==========================================================
set(common
  TAO
  INCLUDE_BASE "${TAO_SOURCE_DIR}"
  # BUILD_SEPARATE
  IDL_FLAGS -SS -Sorb -Sci -iC tao/PortableServer
)
_tao_idl(${common} -Gp -Gd -GA IDL_FILES PortableServer/ForwardRequest.pidl)
_tao_idl(${common} -Gp -Gd -GA -Sal
  IDL_FILES
    PortableServer/AdapterActivator.pidl
    PortableServer/IdAssignmentPolicy.pidl
    PortableServer/IdUniquenessPolicy.pidl
    PortableServer/ImplicitActivationPolicy.pidl
    PortableServer/LifespanPolicy.pidl
    PortableServer/RequestProcessingPolicy.pidl
    PortableServer/ServantActivator.pidl
    PortableServer/ServantLocator.pidl
    PortableServer/ServantManager.pidl
    PortableServer/ServantRetentionPolicy.pidl
    PortableServer/ThreadPolicy.pidl
)
_tao_idl(${common} -Gp -Gd
  IDL_FILES
    PortableServer/POAManager.pidl
    PortableServer/POAManagerFactory.pidl
    PortableServer/POA.pidl
    PortableServer/PS_Current.pidl
)
_tao_idl(${common} -Sa -GX IDL_FILES PortableServer/PortableServer_include.pidl)
_tao_idl(${common} -Sa -GX
  # -Wb,include_guard=TAO_PORTABLESERVER_SAFE_INCLUDE
  # -Wb,safe_include=tao/PortableServer/PortableServer.h
  IDL_FILES PortableServer/PortableServer.pidl
)

_tao_get_generated_output_dir(TAO gen_dir)
target_include_directories(TAO PRIVATE "${TAO_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" "${gen_dir}/tao")
target_include_directories(TAO SYSTEM INTERFACE "${TAO_SOURCE_DIR}")
