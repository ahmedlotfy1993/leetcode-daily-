/**
 * @brief Problem Description:
 * ---------------------------
 * Design a data structure (Router) that can efficiently manage network packets.
 * Each packet has:
 *      - source: machine ID that generated the packet
 *      - destination: target machine ID
 *      - timestamp: time packet arrived at router
 *
 * Operations:
 * -----------
 * 1. Router(int memoryLimit):
 *      - Initializes router with a maximum number of packets that can be stored.
 *      - If adding a new packet exceeds memory limit, the oldest packet must be removed.
 *
 * 2. bool addPacket(int source, int destination, int timestamp):
 *      - Adds a new packet (if not duplicate).
 *      - Returns true if added successfully, false if duplicate.
 *      - Packets are inserted in FIFO order, timestamp is strictly increasing.
 *
 * 3. vector<int> forwardPacket():
 *      - Removes and returns the oldest packet in FIFO order as {source, destination, timestamp}.
 *      - If router is empty, return empty vector.
 *
 * 4. int getCount(int destination, int startTime, int endTime):
 *      - Returns count of packets still stored that match the destination AND
 *        have timestamps within [startTime, endTime].
 *
 * Key Constraints:
 * ----------------
 * - addPacket calls come with strictly increasing timestamps, allowing efficient range queries.
 * - Must be efficient even with large packet counts.
 *
 * Approaches:
 * -----------
 * - Use a deque<Packet> for O(1) FIFO enqueue/dequeue of packets.
 * - Use an unordered_set<Packet> for O(1) duplicate detection.
 * - For getCount() we support two approaches :
 *   1) DESTINATION_INDEXED_TIMESTAMPS :
 *      - Maintain an unordered_map<destination, sorted vector<timestamps>>
 *      - On addPacket: push_back timestamp to vector (O(1) amortized).
 *      - On forwardPacket: erase front timestamp (O(1) since we always remove oldest).
 *      - On getCount: use lower_bound + upper_bound on the list of packets with the same destination.
 *   2) LINEAR_SCAN_PACKETS:
 *      - On getCount: use lower_bound + upper_bound on all packets then count the matching packets with the same destination.
 *
 * Time Complexity:
 * ----------------
 * addPacket(): O(1)  
 * forwardPacket(): O(1)  
 * getCount(): 
 *      - With DESTINATION_INDEXED_TIMESTAMPS → O(log k) where k = number of packets for that destination.
 *      - With LINEAR_SCAN_PACKETS → O(n) worst case.
 *
 * Space Complexity:
 * -----------------
 * O(n) for storing packets + O(n) for destination-to-timestamp map in first approach.
 */

struct Packet {
    int source;
    int destination;
    int timestamp;
    bool operator==(const Packet& rhs) const {
        return rhs.source == source && rhs.destination == destination && rhs.timestamp == timestamp;
    }
};

template <>
struct hash<Packet> {
    size_t operator()(const Packet& p) const noexcept {
        size_t h1 = hash<int>{}(p.source);
        size_t h2 = hash<int>{}(p.destination);
        size_t h3 = hash<int>{}(p.timestamp);
        return h1 ^ h2 ^ h3;
    }
};

#define USE_DESTINATION_INDEXED_TIMESTAMPS 1

class Router {
    deque<Packet> packets;           // Maintains FIFO order of packets
    unordered_set<Packet> packets_set; // For O(1) duplicate detection
#if USE_DESTINATION_INDEXED_TIMESTAMPS
    unordered_map<int, vector<int>> destinationTimestamps; // destination -> sorted timestamps
#endif
    const int PACKETS_LIMIT;

public:
    Router(int memoryLimit) : PACKETS_LIMIT(memoryLimit) {}

    bool addPacket(int source, int destination, int timestamp) {
        Packet new_packet{source, destination, timestamp};
        bool result = false;

        if (!packets_set.count(new_packet)) {
            if (packets.size() >= PACKETS_LIMIT) {
                const Packet& oldest = packets.front();
#if USE_DESTINATION_INDEXED_TIMESTAMPS
                auto& timestamps = destinationTimestamps[oldest.destination];
                timestamps.erase(timestamps.begin()); // remove oldest timestamp
                if (timestamps.empty()) destinationTimestamps.erase(oldest.destination);
#endif
                packets_set.erase(oldest);
                packets.pop_front();
            }
            packets.push_back(new_packet);
            packets_set.insert(new_packet);
#if USE_DESTINATION_INDEXED_TIMESTAMPS
            destinationTimestamps[destination].push_back(timestamp);
#endif
            result = true;
        }
        return result;
    }

    vector<int> forwardPacket() {
        vector<int> packet;
        if (!packets.empty()) {
            const Packet& oldest = packets.front();
            packet = {oldest.source, oldest.destination, oldest.timestamp};
#if USE_DESTINATION_INDEXED_TIMESTAMPS
            auto& timestamps = destinationTimestamps[oldest.destination];
            timestamps.erase(timestamps.begin()); // remove oldest timestamp
            if (timestamps.empty()) destinationTimestamps.erase(oldest.destination);
#endif
            packets_set.erase(oldest);
            packets.pop_front();
        }
        return packet;
    }

    int getCount(int destination, int startTime, int endTime) {
        int count = 0;
#if USE_DESTINATION_INDEXED_TIMESTAMPS
        auto destination_it = destinationTimestamps.find(destination);
        if (destination_it != destinationTimestamps.end()) {
            const auto& timestamps = destination_it->second;
            auto lower = lower_bound(timestamps.begin(), timestamps.end(), startTime);
            auto upper = upper_bound(timestamps.begin(), timestamps.end(), endTime);
            count = distance(lower, upper);
        }
#else
        auto lower = lower_bound(packets.begin(), packets.end(), startTime,
                                 [](const Packet& p, int t) { return p.timestamp < t; });

        auto upper = upper_bound(packets.begin(), packets.end(), endTime,
                                 [](int t, const Packet& p) { return p.timestamp > t; });

        count = count_if(lower, upper,
                         [destination](const Packet& p) { return p.destination == destination; });
#endif
        return count;
    }
};
