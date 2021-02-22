using namespace map;

template <typename K, typename V>
HashMap<K,V>::HashMap(unsigned int bucket_size)
{
    buckets_ = new Bucket[bucket_size]();
    bucket_capacity_ = bucket_size;
    occupied_buckets_ = 0, deleted_buckets_ = 0;

    // default
    probing_type_ = 0;      // 0 : linear probing / 1 : quadratic probing / 2 : double hashing
    resize_flag_ = true;
    if (typeid(V) == typeid(string)){
        RETURN_DEFAULT = EMPTY_STRING;
    } else {
        RETURN_DEFAULT = nullptr;
    }
}

template <typename K, typename V>
HashMap<K,V>::~HashMap()
{
    static_assert(isEmptyTable(), "Attempt to delete empty table");
    delete[] buckets_;
}


template <typename K, typename V>
void HashMap<K,V>::clear()
{
    delete[] buckets_;
    buckets_ = new Bucket[bucket_capacity_]();
    occupied_buckets_ = 0;
    deleted_buckets_ = 0;

    return;
}


template <typename K, typename V>
V HashMap<K,V>::put(K key, V value)
{
    unsigned int hash = hash_key(key);
    unsigned int index_probing;
    unsigned int i;
    V return_value = RETURN_DEFAULT;

    if (doResize()){
        resize();
    }

    for (i = 0; i < bucket_capacity_; i++){
        index_probing = index_probe(hash, i);
        if (isReplacable(key, index_probing) || !containsData(index_probing)){
            break;
        }
    }

    if (i != bucket_capacity_){
        return_value = buckets_[index_probing].pair.second;

        buckets_[index_probing].pair = make_pair(key, value);
        buckets_[index_probing].hash = hash;

        occupied_buckets_++;
    }
    return return_value; 
}

template <typename K, typename V>
V HashMap<K,V>::putIfAbsent(K key, V value)
{
    V value_get = get(key);

    if (value_get == RETURN_DEFAULT){
        return put(key, value);
    }
    return RETURN_DEFAULT;
}


template <typename K, typename V>
void HashMap<K,V>::resize()
{
    unsigned int old_size = bucket_capacity_;
    bucket_capacity_ = old_size * 2; // default... double the current size
    Bucket *new_buckets = new Bucket[bucket_capacity_]();

    for (unsigned int index = 0; index < old_size; index++){
        if (containsData(index)){
            unsigned int hash = buckets_[index].hash;
            unsigned int index_probing;
            unsigned int i;

            for (i = 0; i < bucket_capacity_; i++){
                index_probing = index_probe(hash, i);

                if (new_buckets[index_probing].hash == 0){
                    break;
                }
            }
            // assert (i == bucket_capacity_);
            new_buckets[index_probing] = buckets_[index];
            new_buckets[index_probing].hash = hash;
        }
    }

    delete buckets_;
    buckets_ = new_buckets;
    deleted_buckets_ = 0;

    return;
}

template <typename K, typename V>
V HashMap<K,V>::get(K key)
{
    unsigned int hash = hash_key(key);
    unsigned int index_probing;
    string return_value = RETURN_DEFAULT;

    for (unsigned int i = 0; i < bucket_capacity_; i++)
    {
        index_probing = index_probe(hash, i);

        if (isDeleted(index_probing)){
            continue;
        }
        if (isEmpty(index_probing)){
            break;
        }

        if (isReplacable(key, index_probing)){
            return_value = buckets_[index_probing].pair.second;
            break;
        }
    }
    return return_value;
}

template <typename K, typename V>
V HashMap<K,V>::remove(K key)
{
    unsigned int hash = hash_key(key);
    unsigned int index_probing;
    string return_value = RETURN_DEFAULT;

    for (unsigned int i = 0; i < bucket_capacity_; i++)
    {
        index_probing = index_probe(hash, i);

        if (isDeleted(index_probing)){
            continue;
        }
        if (isEmpty(index_probing)){
            break;
        }

        if (isReplacable(key, index_probing)){
            return_value = buckets_[index_probing].pair.second;
            buckets_[index_probing].hash = DELETED_BUCKET;

            occupied_buckets_--;
            deleted_buckets_++;
            break;
        }
    }
    return return_value;
}

template <typename K, typename V>
bool HashMap<K,V>::remove(K key, V value)
{
    unsigned int hash = hash_key(key);
    unsigned int index_probing;
    string return_value = RETURN_DEFAULT;

    for (unsigned int i = 0; i < bucket_capacity_; i++)
    {
        index_probing = index_probe(hash, i);

        if (isDeleted(index_probing)){
            continue;
        }
        if (isEmpty(index_probing)){
            break;
        }

        if (isReplacable(key, index_probing) && isValueMatch(value, index_probing)){
            buckets_[index_probing].hash = DELETED_BUCKET;

            occupied_buckets_--;
            deleted_buckets_++;
            return true;
        }
    }
    return false;
}

template <typename K, typename V>
V HashMap<K,V>::replace(K key, V value)
{
    unsigned int hash = hash_key(key);
    unsigned int index_probing;
    string return_value = RETURN_DEFAULT;

    for (unsigned int i = 0; i < bucket_capacity_; i++)
    {
        index_probing = index_probe(hash, i);

        if (isDeleted(index_probing)){
            continue;
        }
        if (isEmpty(index_probing)){
            break;
        }

        if (isReplacable(key, index_probing)){
            return_value = buckets_[index_probing].pair.second;
            buckets_[index_probing].pair.second = value;

            break;
        }
    }
    return return_value;
}

template <typename K, typename V>
bool HashMap<K,V>::replace(K key, V old_value, V new_value)
{
    unsigned int hash = hash_key(key);
    unsigned int index_probing;

    for (unsigned int i = 0; i < bucket_capacity_; i++)
    {
        index_probing = index_probe(hash, i);

        if (isDeleted(index_probing)){
            continue;
        }
        if (isEmpty(index_probing)){
            break;
        }

        if (isReplacable(key, index_probing) && isValueMatch(old_value, index_probing)){
            buckets_[index_probing].pair.second = new_value;

            return true;
        }
    }
    return false;
}


template <typename K, typename V>
void HashMap<K,V>::setType(int type){
    probing_type_ = type;
    return;
}

template <typename K, typename V>
void HashMap<K,V>::setResizeFlag(bool flag){
    resize_flag_ = flag;
    return;
}

template <typename K, typename V>
bool HashMap<K,V>::getResizeFlag(){
    return resize_flag_;
}


/*
template <typename K, typename V>
bool HashMap<K,V>::isType(){
    return (probing_type_ == 0 || probing_type_ == 1 || probing_type_ == 2);
}
*/

template <typename K, typename V>
bool HashMap<K,V>::doResize(){
    return (resize_flag_ && occupied_buckets_ >= bucket_capacity_/2);
}

template <typename K, typename V>
bool HashMap<K,V>::isEmptyTable(){
    return (occupied_buckets_ == 0 && deleted_buckets_ == 0);
}

template <typename K, typename V>
bool HashMap<K,V>::isEmpty(unsigned int index_probing){
    return (buckets_[index_probing].hash == 0);
}

template <typename K, typename V>
bool HashMap<K,V>::isDeleted(unsigned int index_probing){
    return (buckets_[index_probing].hash == DELETED_BUCKET);
}

template <typename K, typename V>
bool HashMap<K,V>::containsData(unsigned int index_probing){
    return (!isEmpty(index_probing) && !isDeleted(index_probing));
}

template <typename K, typename V>
bool HashMap<K,V>::isReplacable(K key, unsigned int index_probing){
    return (key == buckets_[index_probing].pair.first);
}

template <typename K, typename V>
bool HashMap<K,V>::isValueMatch(V value, unsigned int index_probing){
    return (value == buckets_[index_probing].pair.second);
}


template <typename K, typename V>
void HashMap<K,V>::bucketStatus()
{
    cout << "... " << occupied_buckets_ << "/" << bucket_capacity_ << " buckets occupied ... " << deleted_buckets_ << "/" << bucket_capacity_ << " buckets deleted ... ";
    cout << " ...approximately " << (float)occupied_buckets_ / bucket_capacity_ * 100 << "% full" << endl;
    return;
}

template <typename K, typename V>
void HashMap<K,V>::printBucket()
{
    cout << endl;
    cout << "---------------------------------------------------------------------------------------------" << endl;
    cout << "index |  hash key  |     key    |    value   | index |  hash key  |     key    |    value   " << endl;
    cout << "---------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < bucket_capacity_; i++){
        cout.setf(ios::right);
        cout << setw(5) << i << " | ";
        if (buckets_[i].hash != 0){
            cout.setf(ios::right);
            cout << setw(10) << buckets_[i].hash << " | ";
            if (buckets_[i].hash != DELETED_BUCKET){
                cout.setf(ios::right);
                cout << setw(10) << buckets_[i].pair.first << " | ";
                cout.setf(ios::right);
                cout << setw(10) << buckets_[i].pair.second << " | ";
            } else {
                cout << setw(10) << " " << " | ";
                cout << setw(10) << " " << " | ";
            }
        } else {
            cout << setw(10) << " " << " | ";
            cout << setw(10) << " " << " | ";
            cout << setw(10) << " " << " | ";
        }
        if (i%2){
            cout << endl;
        }
    }
    cout << endl;
    cout << "---------------------------------------------------------------------------------------------" << endl;
}