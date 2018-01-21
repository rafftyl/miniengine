#pragma once
#include <memory>
#include <queue>

namespace mini
{
	class RendererLayerComparator
	{
	public:
		bool operator()(const std::shared_ptr<class Renderer>& lhs, const std::shared_ptr<Renderer>& rhs) const;
	};

	typedef std::priority_queue<std::shared_ptr<Renderer>,
		std::vector<std::shared_ptr<Renderer>>,
		RendererLayerComparator> RenderingQueue;
}