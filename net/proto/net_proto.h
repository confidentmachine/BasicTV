/*
  net_proto.h: The networking protocol
*/
#include "../net_const.h"
#ifndef NET_PROTO_H
#define NET_PROTO_H
#include "../../id/id.h"
#include <string>
#include <SDL2/SDL_net.h>

/*
  Multiple connections can be made to a single client perfectly fine. However,
  the node you are connecting to will register all of the sockets as individual
  peers. 

  Multiple connections doesn't make much sense unless you want to increase the
  throughput of the Tor network by opening more circuits. SOCKS proxies are 
  somewhat implemented, but the easy creating and destroying of Tor circuits 
  is not (shouldn't be hard).
 */

#define NET_PROTO_MAX_SOCKET_PER_PEER 16

// single identifies the beginning of the metadata, double is single, etc.
#define NET_PROTO_DEV_CTRL_1 0x11

// adjust this value
#define NET_PROTO_META_LENGTH 12

/*
  All API calls rest here, defined in net_proto.cpp
 */

namespace net_proto{
	namespace request{
		void add_id(id_t_ id);
		void add_id(std::vector<id_t_> id);
		void del_id(id_t_ id);
		void del_id(std::vector<id_t_> id);
	};
	namespace peer{
		// IP/URL and port, easy wrapper. Assume default if not called
		void set_self_as_peer(std::string ip, uint16_t port);
		id_t_ get_self_as_peer();
	};
	namespace socket{
		/*
		  Attempts to start min amount of simultaneous connections with
		  a peer. Hopefully will decrease the response time if we have
		  enough threads to effectively spread the load.
		 */
		std::vector<id_t_> connect(id_t_ peer_id_, uint32_t min);
		// TODO: should be a lookup cache system in net_proto_peer_t
		std::vector<id_t_> all_proto_socket_of_peer(id_t_ peer_id);
		id_t_ optimal_proto_socket_of_peer(id_t_ peer_id);
		namespace stats{
			std::vector<id_t_> sort(std::vector<id_t_> socket_ids,
						id_t_ request_id);
		};
	};
};

extern void net_proto_init();
extern void net_proto_loop();
extern void net_proto_close();

#endif
// here for legacy reasons
#include "net_proto_request.h"
#include "net_proto_peer.h"
