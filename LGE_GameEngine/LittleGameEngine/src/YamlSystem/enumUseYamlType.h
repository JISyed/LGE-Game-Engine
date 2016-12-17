#ifndef H_LGE_YAML_USE_YAML_TYPE
#define H_LGE_YAML_USE_YAML_TYPE
namespace lge
{
	// Only used to signify methods where the Yaml Loader System was used. Reduces ambiguity in constructors that need the Yaml Loader.
	enum LgeUseYaml_t
	{
		// Only used to signify methods where the Yaml Loader System was used. Reduces ambiguity in constructors that need the Yaml Loader.
		UseYaml = 0xEDCFFCBA
	};
}
#endif