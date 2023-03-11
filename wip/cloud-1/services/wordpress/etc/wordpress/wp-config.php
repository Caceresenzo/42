<?php
/**
 * The base configuration for WordPress
 *
 * The wp-config.php creation script uses this file during the installation.
 * You don't have to use the web site, you can copy this file to "wp-config.php"
 * and fill in the values.
 *
 * This file contains the following configurations:
 *
 * * Database settings
 * * Secret keys
 * * Database table prefix
 * * ABSPATH
 *
 * @link https://wordpress.org/support/article/editing-wp-config-php/
 *
 * @package WordPress
 */

// ** Database settings - You can get this info from your web host ** //
/** The name of the database for WordPress */
define( 'DB_NAME', 'wordpress' );

/** Database username */
define( 'DB_USER', 'wordpress' );

/** Database password */
define( 'DB_PASSWORD', 'password' );

/** Database hostname */
define( 'DB_HOST', 'database' );

/** Database charset to use in creating database tables. */
define( 'DB_CHARSET', 'utf8mb4' );

/** The database collate type. Don't change this if in doubt. */
define( 'DB_COLLATE', '' );

/**#@+
 * Authentication unique keys and salts.
 *
 * Change these to different unique phrases! You can generate these using
 * the {@link https://api.wordpress.org/secret-key/1.1/salt/ WordPress.org secret-key service}.
 *
 * You can change these at any point in time to invalidate all existing cookies.
 * This will force all users to have to log in again.
 *
 * @since 2.6.0
 */
define( 'AUTH_KEY',         '0]BZD3gMJ>$3&7,)*w7tnk!ZSys{iX_ND>Mp].i}/nce][~H[v~%8Hc;Q@NR7.]l' );
define( 'SECURE_AUTH_KEY',  'ktU0DKpH>9.Ce|}tP[n>FUfgoI{c^sLrEsm.4A8V;#gLsvJQO>oBpWh?c79~^a#i' );
define( 'LOGGED_IN_KEY',    'DR:dJP~!*JjLa&DPS%}V/eKI?kLbO&*86-wweZJ,VjID[/)`cBS{5cT9N`2d:pRw' );
define( 'NONCE_KEY',        'VDt`7xV!J2}bFhY(K#7p~F%TV ^$b?g;/Qbt?CLC=H$_N@6YoH1_sWz~p~IN66(/' );
define( 'AUTH_SALT',        'u/*E#Ix-<=~B>.Poos41}r%<^Yzi!Y(kpGwn Bz-E0L_q_ca7p>7#o0Rr{]s.1ti' );
define( 'SECURE_AUTH_SALT', 'jX^2O{,R@fIT$X864JRp$Q=pUXq_Dpu191(8e~nO7{}?;vHdP-5][N><paP&=Rto' );
define( 'LOGGED_IN_SALT',   '3 UXuF<3~ufjAt&4>jM(ZpXqde1{jgq=/PF)1;}6x~86Ocp@x82bwzG!7e8 |%?3' );
define( 'NONCE_SALT',       '(W]#mrBEwx7GZw#uf)fMzUJd8(4|G*bh<xiLPH8fX5/$,L#C)HSffd)zy.G <}a@' );

/**#@-*/

/**
 * WordPress database table prefix.
 *
 * You can have multiple installations in one database if you give each
 * a unique prefix. Only numbers, letters, and underscores please!
 */
$table_prefix = 'wp_';

/**
 * For developers: WordPress debugging mode.
 *
 * Change this to true to enable the display of notices during development.
 * It is strongly recommended that plugin and theme developers use WP_DEBUG
 * in their development environments.
 *
 * For information on other constants that can be used for debugging,
 * visit the documentation.
 *
 * @link https://wordpress.org/support/article/debugging-in-wordpress/
 */
define( 'WP_DEBUG', true );

/* Add any custom values between this line and the "stop editing" line. */

define( 'WP_AUTO_UPDATE_CORE', false );

/* That's all, stop editing! Happy publishing. */

/** Absolute path to the WordPress directory. */
if ( ! defined( 'ABSPATH' ) ) {
	define( 'ABSPATH', __DIR__ . '/' );
}

/** Sets up WordPress vars and included files. */
require_once ABSPATH . 'wp-settings.php';
