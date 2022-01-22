/*
 * resource_system.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef SYSTEMS_RESOURCE_SYSTEM_H_
#define SYSTEMS_RESOURCE_SYSTEM_H_

#include <vector>
#include "../types.h"

template<typename ResourceT>
class ResourceSystem
{
public:
    ResourceSystem() = default;

    ResourceID add_new(ResourceT resource)
    {
    	m_resources.push_back(std::move(resource));
        return m_resources.size()-1;
    }

    int size() const { return m_resources.size(); }

    optional_ref<ResourceT> operator[](const ResourceID id)
    {
        if(0 <= id && id < static_cast<ResourceID>(size()))
            return optional_ref<ResourceT>{m_resources[id]};
        else
        	return {};
    }

    optional_ref<const ResourceT> operator[](const ResourceID id) const
    {
        if(0 <= id && id < static_cast<ResourceID>(size()))
            return optional_ref<const ResourceT>{m_resources[id]};
        else
        	return {};
    }

    void clear()
    {
        m_resources.clear();
    }


private:
    std::vector<ResourceT> m_resources;
};

#endif /* SYSTEMS_RESOURCE_SYSTEM_H_ */
