#ifndef RENDER_STATES_H_
#define RENDER_STATES_H_

#include <bgfx/bgfx.h>

// Default render state for opaque meshes
constexpr uint64_t kDefaultRenderState =
BGFX_STATE_WRITE_RGB |
BGFX_STATE_WRITE_A |
BGFX_STATE_WRITE_Z |
BGFX_STATE_DEPTH_TEST_LESS |
BGFX_STATE_CULL_CCW |
BGFX_STATE_MSAA;

// Optional: pre-define other states for transparency, wireframe, etc.
constexpr uint64_t kTransparentRenderState =
BGFX_STATE_WRITE_RGB |
BGFX_STATE_WRITE_A |
BGFX_STATE_DEPTH_TEST_LESS |
BGFX_STATE_BLEND_ALPHA |
BGFX_STATE_MSAA;


#endif