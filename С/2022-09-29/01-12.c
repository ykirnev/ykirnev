#include <stdio.h>

int main (void)
{
    int n, m_1, m_2, m_3, change;
    scanf("%d", &n);
    scanf("%d", &m_1);
    scanf("%d", &m_2);
    if (m_2 > m_1)
    {
        change = m_1;
        m_1 = m_2;
        m_2 = change;
    }
    scanf("%d", &m_3);
    if (m_1 < m_3)
    {
        change = m_3;
        m_3 = m_2;
        m_2 = m_1;
        m_1 = change;
    }
    else if (m_2 < m_3)
    {
        change = m_2;
        m_2 = m_3;
        m_3 = change;
    }
    for (int i = 3; i <n; i ++)
    {
        scanf("%d", &change);
        if (m_1 <= change)
        {
            m_3 = m_2;
            m_2 = m_1;
            m_1 = change;
        }
        else if(m_2 <= change)
        {
            m_3 = m_2;
            m_2 = change;
        }
        else if (m_3 <= change)
        {
            m_3 = change;
        }
        
    }
    printf("%d %d %d", m_1, m_2, m_3);
    return 0;
}   