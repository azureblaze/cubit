#include <stdexcept>
#include "DirectRenderer.h"

cubit::impl::DirectRenderer::DirectRenderer(RenderEngine* renderEngine)
    : renderEngine(renderEngine) {}

void cubit::impl::DirectRenderer::render() { renderEngine->present(); }
