#include <string>
#include <cuda.h>
#include "defines.h"
#include "utils.h"


#ifndef TORCH_RADON_PARAMETER_CLASSES_H
#define TORCH_RADON_PARAMETER_CLASSES_H

class VolumeCfg {
public:
    // dimensions of the measured volume
    int depth;
    int height;
    int width;

    // position delta on each axis
    float dz;
    float dy;
    float dx;

    // size of a cell along each axis
    float sz;
    float sy;
    float sx;

    // inverse of size
    float inv_scale_z;
    float inv_scale_y;
    float inv_scale_x;

    bool is_3d;

    VolumeCfg(int d, int h, int w, float _dz, float _dy, float _dx, float _sz, float _sy, float _sx, bool ddd);
};

class ProjectionCfg {
public:
    // number of pixels of the detector and spacing
    int det_count_u;
    float det_spacing_u;
    int det_count_v;
    float det_spacing_v;

    int n_angles;

    // source and detector distances (for fanbeam and coneflat)
    float s_dist = 0.0;
    float d_dist = 0.0;

    // pitch = variation in z after a full rotation (for coneflat)
    float pitch;
    float initial_z;

    int projection_type;

    ProjectionCfg(int dc_u, float ds_u, int dc_v=0, float ds_v=1.0f, float sd=0.0f, float dd=0.0f,
                  float pi=0.0f, float iz=0.0f, int pt=0);

    ProjectionCfg(const ProjectionCfg& src);

    bool is_2d() const;

    ProjectionCfg copy() const;

//    __device__ __inline__ float det_pixel_pos_u(int p) const {
//        //get the position of the detector pixel p on the u axis
//        return (p - det_count_u * 0.5f + 0.5f) * det_spacing_u;
//    }
};

class ExecCfg {
public:
    dim3 block_dim;

    int channels;

    float sampling_rate;

    ExecCfg(int x, int y, int z, int ch, float sr);

    dim3 get_grid_size(int x, int y = 1, int z = 1) const;

    int get_channels(int batch_size) const;
};

#endif
