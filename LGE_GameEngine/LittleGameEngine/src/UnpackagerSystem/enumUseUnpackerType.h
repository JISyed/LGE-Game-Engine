#ifndef H_LGE_PKG_USE_UNPACKER_TYPE
#define H_LGE_PKG_USE_UNPACKER_TYPE
namespace lge
{
	// Only used to signify methods where the Unpacker System was used. Reduces ambiguity in constructors that need the Unpacker.
	enum UseUnpacker_t
	{
		// Only used to signify methods that the Unpacker System was used. Reduces ambiguity in constructors that need the Unpacker.
		UseUnpacker = 0xABCFEDDE
	};
}
#endif