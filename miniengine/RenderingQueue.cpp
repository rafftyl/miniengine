#include "RenderingQueue.h"
#include "Renderer.h"

namespace mini
{
	bool RendererLayerComparator::operator()(const std::shared_ptr<Renderer>& lhs, const std::shared_ptr<Renderer>& rhs) const
	{
		return lhs->getLayer() > rhs->getLayer();
	}
}