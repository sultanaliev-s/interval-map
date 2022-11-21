#ifndef INTERVAL_MAP_H
#define INTERVAL_MAP_H
#include <map>

template<typename K, typename V>
class interval_map {
private:
	V defaultValue;
	std::map<K,V> map;

public:
	interval_map(V const& val)
	: defaultValue(val) {
    }

	// The interval includes keyBegin, but excludes keyEnd.
	void insert(K const& keyBegin, K const& keyEnd, V const& val) {
        if (!(keyBegin < keyEnd)) {
            return;
        }
        if (map.empty()) {
            if (!(val == defaultValue)) {
                map.insert_or_assign(keyBegin, val);
            }
            return;
		}

        auto itBegin = map.lower_bound(keyBegin);
        auto itEnd = map.lower_bound(keyEnd);

        bool isFirst = (itBegin == map.begin());
        bool isIncluded = false;
        auto prev = itBegin;
        if (prev != map.begin() && (--prev)->second == val) {
            isIncluded = true;
        }
        if (itEnd != map.end() && itEnd->second == val) {
            ++itEnd;
        }
        map.erase(itBegin, itEnd);
        if (!(isFirst && val == defaultValue) && !isIncluded) {
            map.insert_or_assign(keyBegin, val);
        }
	}

	V const& operator[](K const& key) const {
		auto it = map.upper_bound(key);
		if(it == map.begin()) {
			return defaultValue;
		} else {
			return (--it)->second;
		}
	}

    // For testing purposes
    int size() {
        return map.size();
    }

    void set(K key, V val) {
        map.insert_or_assign(key, val);
    }

    V get(K key) {
        auto r = map.find(key);
        return r->second;
    }
};

#endif
