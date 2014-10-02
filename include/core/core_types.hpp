/**
 * Provides the ANT namespace includes for the ANT Core includes and
 * variables.
 */

#ifndef   PSM_CORE_TYPES_HPP
    #define   PSM_CORE_TYPES_HPP

/////////////////////////////////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////////////////////////////////
//#include <MGE/ANT_config.hpp>
#include <map>
#include <string>
#include <vector>

/// Inline macro
#define PSM_FORCE_INLINE _forceinline
#define PSM_INLINE inline

#define PSM_OVERRIDE override

namespace psm
{
  /// Status Enumeration for Status Return values
  enum StatusType
  {
    // Values from -99 to 99 are common Error and Good status responses
    StatusAppMissingAsset = -4,  ///< Application failed due to missing asset file
    StatusAppStackEmpty   = -3,  ///< Application States stack is empty
    StatusAppInitFailed   = -2,  ///< Application initialization failed
    StatusError           = -1,  ///< General error status response
    StatusAppOK           =  0,  ///< Application quit without error
    StatusNoError         =  0,  ///< General no error status response
    StatusFalse           =  0,  ///< False status response
    StatusTrue            =  1,  ///< True status response
    StatusOK              =  1   ///< OK status response

    // Values from +-100 to +-199 are reserved for File status responses
  };

  /// Declare data types
  typedef float Real;
  typedef unsigned int UInt;
  typedef unsigned long Ulong;
  typedef float DeltaTime;
  typedef float TimeStamp;
  typedef std::vector<std::string> StringVector;

  // Forward declarations for interfaces
  class IApp;
  class IState;
  class IAssetHandler;

  // Forward declaration for classes
  class AssetManager;
  class StateManager;

  typedef unsigned long EventType;

    /// Declare Asset ID typedef which is used for identifying Asset objects
  typedef std::string typeAssetID;

  /// Declare Asset Handler ID typedef which is used for identifying Asset Handler objects
  typedef std::string typeAssetHandlerID;

  /// Declare Event ID typedef which is used for identifying Event objects
  typedef std::string typeEventID;

  /// Declare Property ID typedef which is used for identifying Properties
  typedef std::string typePropertyID;

  /// Declare State ID typedef which is used for identifying State objects
  typedef std::string typeStateID;

  /// Declare NameValue typedef which is used for config section maps
  typedef std::map<const std::string, const std::string> typeNameValue;

  /// Declare NameValueIter typedef which is used for name,value pair maps
  typedef std::map<const std::string, const std::string>::iterator typeNameValueIter;
    
  //typedef BYTE CharCode;
}

#endif  //ANT_CORE_TYPES_HPP
