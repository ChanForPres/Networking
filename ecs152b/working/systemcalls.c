#include <signal.h>
typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);

#include <poll.h>
struct pollfd {
    int   fd;         /* file descriptor */
    short events;     /* requested events */
    short revents;    /* returned events */
};
// POLLIN main event
int poll(struct pollfd *fds, nfds_t nfds, int timeout);

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
// Domain AF_INET or AF_INET6
// Type SOCK_STREAM or SOCK_DGRAM
// Protocol is either 0 or IPPROTO_TCP/IPPROTO_UDP
int socket(int domain, int type, int protocol);

#include <sys/types.h>
#include <sys/socket.h>
struct sockaddr {
    sa_family_t sa_family;
    char	 sa_data[14];
}
int bind(int sockfd, const struct sockaddr *my_addr, socklen_t addrlen);

#include <sys/types.h>
#include <sys/socket.h>

ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);
ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);