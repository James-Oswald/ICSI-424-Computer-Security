#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
//#include <arpa/inet.h> //Fails?
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/inet.h>

/* This is the structure we shall use to register our function */
static struct nf_hook_ops nfho;

/* This is the hook function itself */
unsigned int hook_func(void *priv, struct sk_buff *skb, const struct nf_hook_state *state){
	struct iphdr* ip_header = ip_hdr(skb);
	if(ip_header->protocol != 6)	//our filters will only use TCP
		return NF_ACCEPT; 

	struct tcphdr* tcp_header = (void*)ip_header+ip_header->ihl*4;
	printk(KERN_INFO "TCP packet to %d to port %d from %d", ip_header->daddr, ntohs(tcp_header->dest), ntohs(tcp_header->source));
	//rule 1, block telnet from A to B
	//inet_pton("10.2.0.5")
	if(ip_header->daddr == 84017162 && tcp_header->dest == htons(23))
		return NF_DROP;
	//rule 2 block website joswald.net
	//inet_pton("192.185.13.60")
	if(ip_header->daddr == 1007532480 && tcp_header->dest == htons(80))
		return NF_DROP;
	//rule 3 block SSH from A to B
	//inet_pton("10.2.0.5")
	if(ip_header->daddr == 84017162 && tcp_header->dest == htons(22))
		return NF_DROP;
	//rule 4 block FTP from A to B
	//inet_pton("10.2.0.5")
	if(ip_header->daddr == 84017162 && tcp_header->dest == htons(21))
		return NF_DROP;
	//rule 5 block website example.com
	//inet_pton("93.184.216.34")
	if(ip_header->daddr == 584628317 && tcp_header->dest == htons(80))
		return NF_DROP;
	return NF_ACCEPT;
}

/* Initialization routine */
int init_module(){ 						/* Fill in our hook structure */
	nfho.hook = hook_func; 				/* Handler function */
	nfho.hooknum = NF_INET_POST_ROUTING; /* First hook for IPv4 */
	nfho.pf = PF_INET;
	nfho.priority = NF_IP_PRI_FIRST; 	/* Make our function first */
	nf_register_hook(&nfho);
	return 0;
}

/* Cleanup routine */
void cleanup_module()
{
	nf_unregister_hook(&nfho);
}