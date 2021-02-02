truncate -s 100m 100m_zeros
cat 100m_zeros | tr '\0' 'j' > 100m
rm 100m_zeros
