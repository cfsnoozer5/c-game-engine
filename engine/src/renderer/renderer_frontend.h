#pragma once

#include "renderer_types.inl"

struct static_mesh_data;

b8 initialize_renderer(u64* memory_requirement, void* state, const char* application_name);
void shutdown_renderer();

void renderer_on_resized(u16 width, u16 height);

b8 renderer_draw_frame(render_packet* packet);