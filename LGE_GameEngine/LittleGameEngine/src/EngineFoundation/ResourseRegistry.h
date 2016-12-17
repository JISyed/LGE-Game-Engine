#ifndef LGE_RESOURCE_REGISTRY_H
#define LGE_RESOURCE_REGISTRY_H

namespace lge
{
	// Interface for registries and managers
	class ResourceRegistry
	{
	public:
		ResourceRegistry() {}
		virtual ~ResourceRegistry() {}

		virtual void Load() = 0;
		virtual void Unload() = 0;
		virtual void Update() = 0;


	private:

	};
}

#endif