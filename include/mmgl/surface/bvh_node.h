//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#ifndef RAYTRACER_BVH_NODE_H
#define RAYTRACER_BVH_NODE_H


#include <algorithm>
#include <cassert>
#include <cstdint>
#include <vector>
#include <limits>
#include <memory>

#include "mmgl/surface/surface.h"

namespace mmgl {

class BVHNode : public Surface {
public:
    friend class Scene;

    friend class Camera;

    virtual BVHNode *clone() const {
        // this is never used
        assert(false);
        return nullptr;
    }

private:
    // create bvh tree with a lot of pointers, scene is in charge of deleting all of these pointers
    static std::unique_ptr<Surface> create_bvh_tree(const std::vector<std::unique_ptr<Surface>>::iterator &begin,
                                                    const std::vector<std::unique_ptr<Surface>>::iterator &end, const BVH &bvh_mode);

    // helper function, compute volume
    static float compute_volume(const std::vector<std::unique_ptr<Surface>>::const_iterator &begin,
                                const std::vector<std::unique_ptr<Surface>>::const_iterator &end);

    // helper function, determine cut position
    static const std::vector<std::unique_ptr<Surface>>::iterator determine_cut(const std::vector<std::unique_ptr<Surface>>::iterator &begin,
                                                                               const std::vector<std::unique_ptr<Surface>>::iterator &end);

    // intersect function, from parent node to all its leaves
    static void intersect(Ray &ray, const BVHNode *const parent, const uintptr_t surface, const Render &flag);

    BVHNode(const std::vector<std::unique_ptr<Surface>>::const_iterator &begin,
            const std::vector<std::unique_ptr<Surface>>::const_iterator &end);

    bool intersect(Ray &, const Render &) const;

    std::string to_string() const;

    std::unique_ptr<Surface> _left;
    std::unique_ptr<Surface> _right;
};

struct BBoxComparable {
    enum class CompareFlag {
        X, Y, Z
    };
    CompareFlag _flag;

    BBoxComparable(const CompareFlag &f = CompareFlag::X) : _flag{f} { }

    bool operator()(const std::unique_ptr<Surface> &l, const std::unique_ptr<Surface> &r) {
        if (_flag == CompareFlag::X) {
            return l->box().min().x() < r->box().min().x();
        } else if (_flag == CompareFlag::Y) {
            return l->box().min().y() < r->box().min().y();
        } else {
            return l->box().min().z() < r->box().min().z();
        }
    }
};

}

#endif //RAYTRACER_BVH_NODE_H
