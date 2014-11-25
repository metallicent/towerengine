#ifndef __TOWERENGINE_H
#define __TOWERENGINE_H

class tMeshPose;
class tAnimation;
struct tKeyFrame;
class tMesh;
struct tTriangle;
class tMaterial;
class tMeshMaterial;
struct tVertex;
struct tEntity;
class tWorld;
class tObject;
class tCamera;
class tPointLight;
class tPointLightShadow;
class tDirectionalLight;
class tDirectionalLightShadow;
class tRenderer;

#include "tresources.h"

#include "vector2.h"
#include "vector.h"
#include "boundingbox.h"
#include "transform.h"
#include "utils.h"
#include "buffers.h"
#include "shader.h"
#include "face_shader.h"
#include "geometry_pass_shader.h"
#include "gbuffer.h"

#include "ambient_lighting_shader.h"
#include "directional_lighting_shader.h"
#include "point_lighting_shader.h"
#include "ssao_lighting_shader.h"

#include "skybox_shader.h"
#include "point_shadow_shader.h"
#include "directional_shadow_shader.h"
#include "post_process_shader.h"
#include "ssao_shader.h"
#include "color_shader.h"
#include "skybox.h"
#include "vertex.h"
#include "triangle.h"
#include "material.h"
#include "mesh_material.h"
#include "mesh.h"
#include "pose.h"
#include "animation.h"
#include "entity.h"
#include "asset.h"
#include "engine.h"
#include "object.h"
#include "meshobject.h"
#include "utilobjects.h"
#include "heightmap.h"
#include "terrain.h"
#include "terrainobject.h"
#include "camera.h"
#include "point_light.h"
#include "directional_light.h"
#include "renderspace.h"
#include "point_light_shadow.h"
#include "directional_light_shadow.h"
#include "character_controller.h"
#include "world.h"
#include "scene_object.h"
#include "scene.h"
#include "renderer.h"

#endif
