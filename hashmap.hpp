using namespace map;

template <typename K>
HashMap<K>::HashMap(unsigned int bucket_size)
{
    buckets_ = new Bucket[bucket_size]();
    size_buckets_ = bucket_size;
    occupied_buckets_ = 0, replaced_key_ = 0;
    DELETED_BUCKET = (Data *)new Data; // syntax check
}

template <typename K>
HashMap<K>::~HashMap()
{
    // assert buckets!=nullpr;

    clear();
}

template <typename K>
void HashMap<K>::clear()
{
    if (buckets_ != nullptr)
    {
        for (unsigned int i = 0; i < size_buckets_; i++)
        {
            if (buckets_[i].data != nullptr && buckets_[i].data != DELETED_BUCKET)
            {
                delete buckets_[i].data;
            }
        }
        delete[] buckets_;
    }
    return;
}

// input : template class key, string value, probing threshold, probing type
// output : total collision happened while inserting the key-value set
template <typename K>
unsigned int HashMap<K>::put(K key, string value, int type)
{
    unsigned int hash = hash_key(key);
    unsigned int index_probing;
    unsigned int i;

    // inclement index whenever collision happened...
    for (i = 0; i < size_buckets_; i++)
    {
        index_probing = index_probe(hash, i, type);

        // when under condition... break the loop
        //if (insertable(...))
        if (buckets_[index_probing].data == DELETED_BUCKET)
        {
            break;
        }
        else if (buckets_[index_probing].data == nullptr)
        {
            break;
        }

        //else if (need_replace...())
        else if (hash == buckets_[index_probing].hash)
        {
            if (key == buckets_[index_probing].data->pair.first)
            {
                replaced_key_++;
                break;
            }
        }
    }

    // when under condition... exit the function
    if (i == size_buckets_)
    {
        return size_buckets_;
    }

    occupied_buckets_++;
    Data *data = new Data;
    data->pair = make_pair(key, value);
    buckets_[index_probing].data = data;
    buckets_[index_probing].hash = hash;

    return i; // return total collision happend
}

// input : probing type
// output : true if successfully resized... false if failed
template <typename K>
bool HashMap<K>::resize(int type)
{
    unsigned int old_size = size_buckets_;
    size_buckets_ = old_size * 2; // default... double the current size
    Bucket *new_buckets = new Bucket[size_buckets_]();

    // iterate over the old bucket...
    for (unsigned int index = 0; index < old_size; index++)
    {
        // when under condition... continue the loop
        if (buckets_[index].data == nullptr || buckets_[index].data == DELETED_BUCKET)
        {
            continue;
        }
        else
        {
            // notice I'm not hashing again.. using previously computed and saved hash value
            unsigned int hash = buckets_[index].hash;
            unsigned int index_probing;
            unsigned int i;

            // inclement index whenever collision happened...
            for (i = 0; i < size_buckets_; i++)
            {
                index_probing = index_probe(hash, i, type);

                // when under condition... break the loop...
                // notice new bucket cannot have deleted bucket... no need to check
                if (new_buckets[index_probing].data == nullptr)
                {
                    break;
                }
            }
            // this shouldn't happen
            if (i == size_buckets_)
            {
                return false;
            }
            new_buckets[index_probing] = buckets_[index];
            new_buckets[index_probing].hash = hash;
        }
    }

    delete buckets_;

    buckets_ = new_buckets;

    return true;
}

// input : template class key, probing type
// output : string value corresponding to the inserted key... empty string otherwise
template <typename K>
string HashMap<K>::get(K key, int type)
{
    unsigned int hash = hash_key(key);
    unsigned int index_probing;
    string return_string = "";

    // inclement index whenever collision happened...
    for (unsigned int i = 0; i < size_buckets_; i++)
    {
        index_probing = index_probe(hash, i, type);

        // when deleted bucket.. continue
        if (buckets_[index_probing].data == DELETED_BUCKET)
        {
            continue;
        }
        // when nullptr... break... key not in table...
        else if (buckets_[index_probing].data == nullptr)
        {
            break;
        }

        // when current key matches with the saved key, return corresponding value
        else if (hash == buckets_[index_probing].hash)
        {
            if (key == buckets_[index_probing].data->pair.first)
            {
                return_string = buckets_[index_probing].data->pair.second;
                break;
            }
            continue;
        }
    }
    // return empty string when couldn't find any corresponding key
    return return_string;
}

// input : template class key, probing type
// output : string value corresponding to the inserted key... empty string otherwise
template <typename K>
string HashMap<K>::remove(K key, int type)
{
    unsigned int hash = hash_key(key);
    unsigned int index_probing;
    string return_string = "";

    for (unsigned int i = 0; i < size_buckets_; i++)
    {
        index_probing = index_probe(hash, i, type);
        // Bucket *tmp = buckets_[index_probing]; 

        if (buckets_[index_probing].data == DELETED_BUCKET)
        {
            continue;
        }
        else if (buckets_[index_probing].data == nullptr)
        {
            break;
        }

        else if (hash == buckets_[index_probing].hash)
        {
            if (key == buckets_[index_probing].data->pair.first)
            {
                return_string = buckets_[index_probing].data->pair.second;
                delete buckets_[index_probing].data;
                buckets_[index_probing].data = DELETED_BUCKET;

                occupied_buckets_--;
                break;
            }
            continue;
        }
    }
    return return_string;
}

// input : template class key, string value, probing type
// output : true if successfully deleted the data... false otherwise
template <typename K>
bool HashMap<K>::remove(K key, string value, int type)
{
    unsigned int hash = hash_key(key);
    unsigned int index_probing;

    for (unsigned int i = 0; i < size_buckets_; i++)
    {
        index_probing = index_probe(hash, i, type);

        if (buckets_[index_probing].data == DELETED_BUCKET)
        {
            continue;
        }
        else if (buckets_[index_probing].data == nullptr)
        {
            break;
        }

        else if (hash == buckets_[index_probing].hash)
        {
            if (key == buckets_[index_probing].data->pair.first && value == buckets_[index_probing].data->pair.second)
            {
                delete buckets_[index_probing].data;
                buckets_[index_probing].data = DELETED_BUCKET;
                occupied_buckets_--;

                return true;
            }
            continue;
        }
    }
    return false;
}

// input : template class key, string value, probing type
// output : string value corresponding to the inserted key... empty string otherwise
template <typename K>
string HashMap<K>::replace(K key, string value, int type)
{
    unsigned int hash = hash_key(key);
    unsigned int index_probing;
    string return_string = "";

    for (unsigned int i = 0; i < size_buckets_; i++)
    {
        index_probing = index_probe(hash, i, type);

        if (buckets_[index_probing].data == DELETED_BUCKET)
        {
            continue;
        }
        else if (buckets_[index_probing].data == nullptr)
        {
            break;
        }

        else if (hash == buckets_[index_probing].hash)
        {
            if (key == buckets_[index_probing].data->pair.first)
            {
                return_string = buckets_[index_probing].data->pair.second;
                buckets_[index_probing].data->pair.second = value;

                replaced_key_++;
                break;
            }
            continue;
        }
    }
    return return_string;
}

// input : template class key, string old value, string new value, probing type
// output : true if successfully replaced the data... false otherwise
template <typename K>
bool HashMap<K>::replace(K key, string old_value, string new_value, int type)
{
    unsigned int hash = hash_key(key);
    unsigned int index_probing;

    for (unsigned int i = 0; i < size_buckets_; i++)
    {
        index_probing = index_probe(hash, i, type);

        if (buckets_[index_probing].data == DELETED_BUCKET)
        {
            continue;
        }
        else if (buckets_[index_probing].data == nullptr)
        {
            break;
        }
        else if (hash == buckets_[index_probing].hash)
        {
            if (key == buckets_[index_probing].data->pair.first && old_value == buckets_[index_probing].data->pair.second)
            {
                pair<string, string> pair = make_pair(key, new_value);
                buckets_[index_probing].data->pair = pair;
                replaced_key_++;

                return true;
            }
            continue;
        }
    }
    return false;
}

template <typename K>
void HashMap<K>::bucketStatus()
{
    cout << "... " << occupied_buckets_ << "/" << size_buckets_ << " buckets occupied ... " << replaced_key_ << " keys replaced";
    cout << " ...approximately " << (float)occupied_buckets_ / size_buckets_ * 100 << "% full" << endl;
    return;
}

template <typename K>
void HashMap<K>::printBucket()
{
    cout << endl;
    cout << "---------------------------------------------------------------------------------------------" << endl;
    cout << "index |  hash key  |     key    |    value   | index |  hash key  |     key    |    value   " << endl;
    cout << "---------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < size_buckets_; i++){
        cout.setf(ios::right);
        cout << setw(5) << i << " | ";
        if (buckets_[i].data != nullptr){
            cout.setf(ios::right);
            cout << setw(10) << buckets_[i].hash << " | ";
            if (buckets_[i].data != DELETED_BUCKET){
                cout.setf(ios::right);
                cout << setw(10) << buckets_[i].data->pair.first << " | ";
                cout.setf(ios::right);
                cout << setw(10) << buckets_[i].data->pair.second << " | ";
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