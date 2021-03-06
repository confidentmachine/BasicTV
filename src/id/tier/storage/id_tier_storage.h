#ifndef ID_TIER_STORAGE_H
#define ID_TIER_STORAGE_H

struct id_tier_state_storage_t{
private:
	uint8_t flags = 0;
	uint64_t total_bytes = 0;
	uint64_t used_bytes = 0;

	uint64_t last_refresh_micro_s = 0;
	uint64_t refresh_interval_micro_s = 0;
	data_id_t *id = nullptr;

	std::vector<uint8_t> ids;
	std::vector<mod_inc_t_> mod_incs;
	std::vector<uint8_t> extras;
public:
	id_tier_state_storage_t();
	~id_tier_state_storage_t();
	
	void list_virtual_data(data_id_t *id_);
	GET_SET_V(flags, uint8_t);
	GET_SET_V(total_bytes, uint64_t);
	GET_SET_V(used_bytes, uint64_t);

	GET_SET_V(last_refresh_micro_s, uint64_t);
	GET_SET_V(refresh_interval_micro_s, uint64_t);

	ADD_DEL_VECTOR_V(mod_incs, mod_inc_t_);

	std::vector<id_t_> get_ids();
	void set_ids(std::vector<id_t_> ids_);
	
	GET_SET_V(mod_incs, std::vector<mod_inc_t_>);
	GET_SET_V(extras, std::vector<uint8_t>);

	bool is_allowed_extra(uint8_t extra, id_t_ id_);
	
	void add_id_buffer(std::pair<id_t_, mod_inc_t_> tmp);
	void del_id_buffer(id_t_ id_);
	void set_id_buffer(std::vector<std::pair<id_t_, mod_inc_t_> > tmp);
};

#endif
