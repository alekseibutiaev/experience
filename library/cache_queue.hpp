#include <list>

template< typename type_t >
class cache_queue {
public:

	typedef type_t value_t;
	typedef std::list<type_t> queue_t; 

public:

	void add( const type_t& value ) {
		if( !cache_node.empty() ) {
			queue.splice( queue.end(), cache_node, cache_node.begin() );
			queue.back() = value;
		}
		else
			queue.emplace_back( value );
	}

	type_t& front() {
		return queue.front();
	}

	void store_front() {
		cache_node.splice( cache_node.end(), queue, queue.begin() );
	}

	bool empty() const {
		return queue.empty();
	}

	queue_t& data() {
		return queue;
	}

	void store_data( queue_t& value ) {
		cache_node.splice( cache_node.end(), value );
	}

private:

	queue_t queue;
	queue_t cache_node;

};

