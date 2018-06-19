# Zabbix configuration
## Server installation
### Getting the repository
```bash
wget http://repo.zabbix.com/zabbix/3.0/ubuntu/pool/main/z/zabbix-release/zabbix-release_3.0-1%2Bxenial_all.deb
dpkg -i zabbix-release_3.0-1+bionic_all.deb
apt-get update
```
*For other versions of Ubuntu substitute xenial with other version*
### Server with postgreSQL installation
```bash
apt-get install zabbix-server-pgsql zabbix-frontend-php
```
### Database setup
```bash
psql -U <username>
```
Inside psql:
```
create database zabbix;
\q
```
Edit `/etc/zabbix/zabbix_server.conf`:
```
DBName=<username>
DBPassword=<username_password>
```
### Starting zabbix process automatically
```bash
service zabbix-server start
update-rc.d zabbix-server enable #make zabbix start at system boot
```
### PHP configuration for Zabbix frontend
Edit `/etc/zabbix/apache.conf`:
```
php_value date.timezone Europe/Warsaw
```
Restart Apache web server:
```bash
service apache2 restart
```
### Frontend configuration
Open in browser `http://localhost/zabbix`

Click `Next step` button - *Check of pre-requisites*. Usually some php modules have to be installed. Everytime something is changed apache2 has to be restarted (not sure about this).

Click `Next step` button - *Configure DB connection*. Enter details. If database connection error appears, try to connect to it from bash:
```bash
psql -h localhost -U <username> zabbix
``` 
If only MySQL is available, php_version-pgsql has to be installed.

Click `Next step` button - *Zabbix server details*. No modifications are required.

Click `Next step` button - *Pre-installation summary*. If the webserver user has write access to `conf/` directory, the configuration file will be saved automatically and no action is needed. Otherwise you have to download it and put it to the right place (shown in the window).

Click `Next step` and `Finish`.

### Frontend login
Now you can log in the frontend with the following credentials:
* default user name **Admin**;
* default password **zabbix**.
