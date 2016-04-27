//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#include "surface/bvh_node.h"

Surface *BVHNode::create_bvh_tree(const std::vector<Surface *>::iterator &begin,
                                  const std::vector<Surface *>::iterator &end) {
    if (begin == end) {
        return nullptr;
    } else if (begin + 1 == end) {
        return *begin;
    } else {
        BVHNode *node = new BVHNode(begin, end);
        float x_span = node->box().max().x() - node->box().min().x();
        float y_span = node->box().max().y() - node->box().min().y();
        float z_span = node->box().max().z() - node->box().min().z();
        BBoxComparable::CompareFlag flag = BBoxComparable::CompareFlag::X;
        if (y_span > z_span && y_span > x_span) {
            flag = BBoxComparable::CompareFlag::Y;
        } else if (z_span > x_span && z_span > y_span) {
            flag = BBoxComparable::CompareFlag::Z;
        }
        std::sort(begin, end, BBoxComparable{flag});
        // volume based cut --- binary search
        std::vector<Surface *>::iterator median = determine_cut(begin, end);

        node->_left = create_bvh_tree(begin, median);
        node->_right = create_bvh_tree(median, end);
        return node;
    }
}

std::string BVHNode::to_string() const {
    return "BHV Node has nothing to display!";
}

bool BVHNode::intersect(Ray &ray, const Render &flag) const {
    return box_intersect(ray).first;
}

void BVHNode::intersect(Ray &ray, const BVHNode *const parent, const Surface *const surface, const Render &flag) {

    const Surface *const left = parent->_left;
    const Surface *const right = parent->_right;

    const BVHNode *const node_left = dynamic_cast<const BVHNode *const>(left);
    const BVHNode *const node_right = dynamic_cast<const BVHNode *const>(right);

    // 1. left can be nullptr, node, leaf
    // 2. right can be nullptr, node, leaf

    float left_hit_t = std::numeric_limits<float>::infinity();
    float right_hit_t = std::numeric_limits<float>::infinity();
    bool left_hit = false;
    bool right_hit = false;

    if (left) {
        if (node_left) {
            std::pair<bool, float> left_result = left->box_intersect(ray, true);
            if (left_result.first) {
                left_hit_t = left_result.second;
                left_hit = true;
            }
        } else if (left != surface) {
            left->intersect(ray, flag);
        }
    }

    if (right) {
        if (node_right) {
            std::pair<bool, float> right_result = right->box_intersect(ray, true);
            if (right_result.first) {
                right_hit_t = right_result.second;
                right_hit = true;
            }
        } else if (right != surface) {
            right->intersect(ray, flag);
        }
    }

    if (ray.has_intersect() && (std::min(left_hit_t, right_hit_t) > ray.intersection().t())) {
        return;
    }

    if (left_hit && right_hit) {
        if (left_hit_t < right_hit_t) {
            intersect(ray, node_left, surface, flag);
            intersect(ray, node_right, surface, flag);
        } else {
            intersect(ray, node_right, surface, flag);
            intersect(ray, node_left, surface, flag);
        }
    } else if (left_hit) {
        intersect(ray, node_left, surface, flag);
    } else if (right_hit) {
        intersect(ray, node_right, surface, flag);
    }
}

const std::vector<Surface *>::iterator BVHNode::determine_cut(const std::vector<Surface *>::iterator &begin,
                                                              const std::vector<Surface *>::iterator &end) {
    unsigned long size = end - begin;
    unsigned long median = size / 2;
    unsigned long first = 0, last = size;
    unsigned long prev_median = 0;
    while (median > 1 && median < size - 1 && prev_median != median) {
        float left = BVHNode::compute_volume(begin, begin + median);
        float right = BVHNode::compute_volume(begin + median, end);
        if (left >= right) {
            last = median;
        } else {
            first = median;
        }
        prev_median = median;
        median = (first + last) / 2;
    }
    return begin + median;
}


float BVHNode::compute_volume(const std::vector<Surface *>::const_iterator &begin,
                              const std::vector<Surface *>::const_iterator &end) {
    float x_min, y_min, z_min, x_max, y_max, z_max;
    std::vector<Surface *>::const_iterator iter = begin;
    x_min = (*iter)->box().min().x();
    y_min = (*iter)->box().min().y();
    z_min = (*iter)->box().min().z();
    x_max = (*iter)->box().max().x();
    y_max = (*iter)->box().max().y();
    z_max = (*iter)->box().max().z();
    for (iter += 1; iter != end; ++iter) {
        const BBox &temp = (*iter)->box();
        x_min = std::min(temp.min().x(), x_min);
        y_min = std::min(temp.min().y(), y_min);
        z_min = std::min(temp.min().z(), z_min);
        x_max = std::max(temp.max().x(), x_max);
        y_max = std::max(temp.max().y(), y_max);
        z_max = std::max(temp.max().z(), z_max);
    }

    return (x_max - x_min) * (y_max - y_min) * (z_max - z_min);
}

BVHNode::BVHNode(const std::vector<Surface *>::const_iterator &begin, const std::vector<Surface *>::const_iterator &end)
        : _left{nullptr}, _right{nullptr} {
    float x_min, y_min, z_min, x_max, y_max, z_max;
    std::vector<Surface *>::const_iterator iter = begin;
    x_min = (*iter)->box().min().x();
    y_min = (*iter)->box().min().y();
    z_min = (*iter)->box().min().z();
    x_max = (*iter)->box().max().x();
    y_max = (*iter)->box().max().y();
    z_max = (*iter)->box().max().z();
    for (iter += 1; iter != end; ++iter) {
        const BBox &temp = (*iter)->box();
        x_min = std::min(temp.min().x(), x_min);
        y_min = std::min(temp.min().y(), y_min);
        z_min = std::min(temp.min().z(), z_min);
        x_max = std::max(temp.max().x(), x_max);
        y_max = std::max(temp.max().y(), y_max);
        z_max = std::max(temp.max().z(), z_max);
    }
    box(x_min, y_min, z_min, x_max, y_max, z_max);
}
