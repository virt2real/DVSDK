/* -*- C -*-
This is part of the audio CD player library
Copyright (C)1998-99 Tony Arcieri

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with this library; if not, write to the
Free Software Foundation, Inc., 59 Temple Place - Suite 330,
Boston, MA  02111-1307, USA.
*/

/* WARNING: do not modify cdaudio.h, it is generated from cdaudio.h.in */

#ifndef _CDAUDIO_H
#define _CDAUDIO_H

#define LIBCDAUDIO_VERSION_MAJOR 0
#define LIBCDAUDIO_VERSION_MINOR 99
#define LIBCDAUDIO_VERSION_MICRO 12

#define LIBCDAUDIO_VERSION \
        ((LIBCDAUDIO_VERSION_MAJOR<<16)| \
         (LIBCDAUDIO_VERSION_MINOR<< 8)| \
         (LIBCDAUDIO_VERSION_MICRO))

/* Used with disc_info */
enum cd_cdaudio_status_t {
  CDAUDIO_PLAYING, CDAUDIO_PAUSED, CDAUDIO_COMPLETED,
  CDAUDIO_NOSTATUS, CDAUDIO_INVALID, CDAUDIO_ERROR
};

#if 0
#define CDAUDIO_PLAYING                         0
#define CDAUDIO_PAUSED                          1
#define CDAUDIO_COMPLETED                       2
#define CDAUDIO_NOSTATUS                        3
#define CDAUDIO_INVALID                         4
#define CDAUDIO_ERROR                           5
#endif

enum cd_track_type_t { CDAUDIO_TRACK_AUDIO, CDAUDIO_TRACK_DATA };

#if 0
#define CDAUDIO_TRACK_AUDIO                     0
#define CDAUDIO_TRACK_DATA                      1
#endif

#define MAX_TRACKS                              100
#define MAX_SLOTS                               100 /* For CD changers */

/* CDDB defaults */
#define CDDB_PROTOCOL_LEVEL                     3
#define CDDBP_DEFAULT_PORT                      888
#define HTTP_DEFAULT_PORT                       80
#define CDDB_EMAIL_SUBMIT_ADDRESS               "freedb-submit@freedb.org"
#define HTTP_SUBMIT_CGI                         "/~cddb/submit.cgi"
#define CDINDEX_SUBMIT_CGI                      "/cgi-bin/cdi/xsubmit.pl"
#define CDDB_SUBMIT_HTTP                        0
#define CDDB_SUBMIT_EMAIL                       1
#define CDDB_SUBMIT_MODE                        0
#define CDDB_MAX_SERVERS                        128
#define MAX_INEXACT_MATCHES                     16
#define EXTENDED_DATA_SIZE                      4096
#define DISC_ART_SIZE                           32768
#define CDINDEX_ID_SIZE                         30

/* Connection modes */
enum cd_connection_mode_t {
  CDDB_MODE_CDDBP, CDDB_MODE_HTTP, CDINDEX_MODE_HTTP,
  COVERART_MODE_HTTP
};

enum cd_cddb_access_t { CDDB_ACCESS_LOCAL, CDDB_ACCESS_REMOTE };
enum cd_cddb_proxy_t { CDDB_PROXY_DISABLED, CDDB_PROXY_ENABLED };

#if 0
#define CDDB_MODE_CDDBP                         0
#define CDDB_MODE_HTTP                          1
#define CDINDEX_MODE_HTTP                       2
#define COVERART_MODE_HTTP                      3
#define CDDB_ACCESS_LOCAL                       0
#define CDDB_ACCESS_REMOTE                      1
#define CDDB_PROXY_DISABLED                     0
#define CDDB_PROXY_ENABLED                      1
#endif

/* CDDB genres */
enum cd_cddb_genre_t {
  CDDB_UNKNOWN, CDDB_BLUES, CDDB_CLASSICAL, CDDB_COUNTRY, CDDB_DATA,
  CDDB_FOLK, CDDB_JAZZ, CDDB_MISC, CDDB_NEWAGE, CDDB_REGGAE,
  CDDB_ROCK, CDDB_SOUNDTRACK
};

#if 0
#define CDDB_UNKNOWN                            0
#define CDDB_BLUES                              1
#define CDDB_CLASSICAL                          2
#define CDDB_COUNTRY                            3
#define CDDB_DATA                               4
#define CDDB_FOLK                               5
#define CDDB_JAZZ                               6
#define CDDB_MISC                               7
#define CDDB_NEWAGE                             8
#define CDDB_REGGAE                             9
#define CDDB_ROCK                               10
#define CDDB_SOUNDTRACK                         11
#endif

/* CD Index artist types */
enum cd_cdindex_artist_t {
  CDINDEX_SINGLE_ARTIST, CDINDEX_MULTIPLE_ARTIST
};

#if 0
#define CDINDEX_SINGLE_ARTIST                   0
#define CDINDEX_MULTIPLE_ARTIST                 1
#endif

/* Play function options */
enum cd_play_function_t {
  PLAY_START_TRACK=0, PLAY_END_TRACK=1,
  PLAY_START_POSITION=2, PLAY_END_POSITION=4
};

#if 0
#define PLAY_START_TRACK                        0
#define PLAY_END_TRACK                          1
#define PLAY_START_POSITION                     2
#define PLAY_END_POSITION                       4
#endif

#ifndef __LIBCDAUDIO_INTERNAL

#define cdindex_write_disc_data(cd_desc, data) \
        cdindex_write_data(cd_desc, &data)
#define cddb_write_disc_data(cd_desc, data) \
        cddb_write_data(cd_desc, &data)
#define cddb_erase_entry(data) \
        cddb_erase_data(&data)

extern char cddb_message[256];
extern int parse_disc_artist;
extern int parse_track_artist;
extern int cddb_submit_method;
extern char *cddb_submit_email_address;

#endif /* __LIBCDAUDIO_INTERNAL */

/* CDDB entry */
struct cddb_entry {
  int entry_present;                           /* Is there an entry? */
  long entry_timestamp;                        /* Last modification
                                                  time */
  unsigned long entry_id;                      /* CDDB ID of entry */
  char entry_cdindex_id[CDINDEX_ID_SIZE];      /* CD Index ID of entry */
  enum cd_cddb_genre_t entry_genre;            /* CDDB genre of entry */
};

/* CDDB configuration */
struct cddb_conf {
  enum cd_cddb_access_t conf_access;           /* CDDB_ACCESS_LOCAL or
						  CDDB_ACCESS_REMOTE */
  enum cd_cddb_proxy_t conf_proxy;             /* Is a proxy being
                                                  used? */
};
        
/* Server retrieval structure */
struct cddb_server {
  char server_name[256];                        /* Server name */
  int server_port;                              /* Server port */
};

/* CDDB server list structure */
struct cddb_host {
  struct cddb_server host_server;
  char host_addressing[256];
  int host_protocol;
};

/* CDDB hello structure */
struct cddb_hello {
  char hello_program[256];                      /* Program name*/
  char hello_version[256];                      /* Version */
};

/* An entry in the query list */
struct query_list_entry {
  enum cd_cddb_genre_t list_genre;             /* CDDB genre of entry */
  unsigned long list_id;                       /* CDDB ID of entry */
  char list_title[64];                         /* Title of entry */
  char list_artist[64];                        /* Entry's artist */
};

/* TOC data for CDDB query */
struct cddb_direct_query_toc {
  unsigned long toc_id;
  int tracks;
  int positions[MAX_TRACKS];
};

/* CDDB query structure */
enum cd_cddb_query_result_t { QUERY_NOMATCH, QUERY_EXACT, QUERY_INEXACT };

struct cddb_query {
#if 0
#define QUERY_NOMATCH                           0
#define QUERY_EXACT                             1
#define QUERY_INEXACT                           2
#endif
  enum cd_cddb_query_result_t query_match;      /* Uses above
                                                   definitions */
  int query_matches;                            /* Number of matches */
  struct query_list_entry query_list[MAX_INEXACT_MATCHES];
};

/* Used for keeping track of times */
struct disc_timeval {
  int minutes;
  int seconds;
  int frames;
};

/* Brief disc information */
struct disc_status {
  int status_present;                           /* Is disc present? */
  enum cd_cdaudio_status_t status_mode;         /* Disc mode */
  struct disc_timeval status_disc_time;         /* Current disc time */
  struct disc_timeval status_track_time;        /* Current track time */
  int status_current_track;                     /* Current track */
};

/* Track specific information */
struct track_info {
  struct disc_timeval track_length;             /* Length of track */
  struct disc_timeval track_pos;                /* Position of track */
  int track_lba;                                /* Logical Block
                                                   Address */
  enum cd_track_type_t track_type;              /* CDAUDIO_TRACK_AUDIO
                                                   or
                                                   CDAUDIO_TRACK_DATA */
};

/* Disc information such as current track, amount played, etc */
struct disc_info {
  int disc_present;                             /* Is disc present? */
  enum cd_cdaudio_status_t disc_mode;           /* Current disc mode */
  struct disc_timeval disc_track_time;          /* Current track time */
  struct disc_timeval disc_time;                /* Current disc time */
  struct disc_timeval disc_length;              /* Total disc length */
  int disc_current_track;                       /* Current track */
  int disc_first_track;                         /* First track on the
                                                   disc */
  int disc_total_tracks;                        /* Number of tracks on
                                                   disc */
  struct track_info disc_track[MAX_TRACKS];     /* Track specific
                                                   information */
};

/* Invisible volume structure */
struct __volume { 
  int left;
  int right;
};

/* Volume structure */
struct disc_volume {
  struct __volume vol_front;                    /* Normal volume
                                                   settings */
  struct __volume vol_back;                     /* Surround sound
                                                   volume settings */
};

struct art_query_entry {
  char list_album[64];
  char list_artist[64];
  struct cddb_host list_host;
};

/* Disc art query structure */
struct art_query {
  enum cd_cddb_query_result_t query_match;      /* Uses same values as
                                                   cddb_query */
  int query_matches;                            /* Number of matches */
  struct art_query_entry query_list[MAX_INEXACT_MATCHES];
};

/* Cover art structure */
struct art_data {
  int art_present;                              /* Is art present? */
  int art_length;                               /* Size of image */
  char art_mime_type[16];                       /* MIME type of image */
  char art_image[DISC_ART_SIZE];                /* Stored image */
};

/* Compact cover art structure */
struct art_mc_data {
  int art_present;
  int art_length;
  char art_mime_type[16];
  char *art_data;
};

/* Track database structure */
struct track_data {
  char track_name[256];                         /* Track name */
  char track_artist[256];                       /* Track specific
                                                   artist */
  char track_extended[EXTENDED_DATA_SIZE];      /* Extended
                                                   information */
};

/* Disc database structure */
struct disc_data {
  unsigned long data_id;                        /* CDDB ID */
  char data_cdindex_id[CDINDEX_ID_SIZE];        /* CD Index ID */
  int data_revision;                            /* CDDB revision
                                                   (incremented with
                                                   each submit) */
  char data_title[256];                         /* Disc title */
  char data_artist[256];                        /* Album artist */
  char data_extended[EXTENDED_DATA_SIZE];       /* Extended
                                                   information */
  enum cd_cddb_genre_t data_genre;              /* Disc genre */
  enum cd_cdindex_artist_t data_artist_type;    /* Single or multiple
                                                   artist CD */
  struct track_data data_track[MAX_TRACKS];     /* Track names */
};

/* Compact track database structure */
struct track_mc_data {
  int track_name_len;
  char *track_name;
  int track_artist_len;
  char *track_artist;
  int track_extended_len;
  char *track_extended;
};

/* Compact disc database structure */
struct disc_mc_data {
  unsigned long data_id;
  char data_cdindex_id[CDINDEX_ID_SIZE];
  int data_title_len;
  char *data_title;
  int data_artist_len;
  char *data_artist;
  int data_extended_len;
  char *data_extended;
  enum cd_cddb_genre_t data_genre;
  int data_revision;
  enum cd_cdindex_artist_t data_artist_type;
  int data_total_tracks;
  struct track_mc_data **data_track;
};

/* Summary of a single disc in the changer */
struct disc_summary {
  int disc_present;                             /* Is disc present? */
  struct disc_timeval disc_length;              /* Length of disc */
  int disc_total_tracks;                        /* Total tracks */
  unsigned long disc_id;                        /* CDDB ID */
  char data_cdindex_id[CDINDEX_ID_SIZE];        /* CDI ID */
  char disc_info[128];                          /* Artist name / Disc
                                                   name */
  struct art_data data_art;                     /* Disc art */
};

/* Disc changer structure */
struct disc_changer {
  int changer_slots;
  struct disc_summary changer_disc[MAX_SLOTS];
};

/* Compact disc summary */
struct disc_mc_summary {
  int disc_present;
  struct disc_timeval disc_length;
  int disc_total_tracks;
  unsigned long disc_id;
  char data_cdindex_id[CDINDEX_ID_SIZE];
  int disc_info_len;
  char *disc_info;
  struct art_mc_data data_art;
};

/* Compact disc changer structure */
struct disc_mc_changer {
  int changer_slots;
  struct disc_mc_summary **changer_disc;
};

/* CDDB server list structure */
struct cddb_serverlist {
  int list_len;
  struct cddb_host list_host[CDDB_MAX_SERVERS];
};

#ifdef __cplusplus
extern "C" {
#endif

extern long cdaudio_getversion(void);

/* Function prototopes */
void cd_version(char *buffer, int len);

int cd_frames_to_lba(int frames);
int cd_lba_to_frames(int lba);
int cd_msf_to_frames(struct disc_timeval time);
int cd_msf_to_lba(struct disc_timeval time);
void cd_frames_to_msf(struct disc_timeval *time, int frames);
void cd_lba_to_msf(struct disc_timeval *time, int frames);

int cd_init_device(char *device_name);
int cd_finish(int cd_desc);
int cd_stat(int cd_desc, struct disc_info *disc);
int cd_poll(int cd_desc, struct disc_status *status);
int cd_update(struct disc_info *disc, struct disc_status status);

int cd_play_frames(int cd_desc, int startframe, int endframe);
int cd_playctl(int cd_desc, int options, int start_track, ...);
int cd_play_track_pos(int cd_desc, int starttrack,
		      int endtrack, int startpos);
int cd_play_track(int cd_desc, int starttrack, int endtrack);
int cd_play_pos(int cd_desc, int track, int startpos);
int cd_play(int cd_desc, int track);

int cd_track_advance(int cd_desc, int endtrack,
		     struct disc_timeval time);
int cd_advance(int cd_desc, struct disc_timeval time);
int cd_stop(int cd_desc);
int cd_pause(int cd_desc);
int cd_resume(int cd_desc);
int cd_eject(int cd_desc);
int cd_close(int cd_desc);

int cd_set_volume(int cd_desc, struct disc_volume vol);
int cd_get_volume(int cd_desc, struct disc_volume *vol);

long cddb_discid(int cd_desc);
int cddb_process_url(struct cddb_host *host, const char *url);
int cddb_read_serverlist(struct cddb_conf *conf,
			 struct cddb_serverlist *list,
			 struct cddb_server *proxy);
int cddb_write_serverlist(struct cddb_conf conf,
			  struct cddb_serverlist list,
			  struct cddb_server proxy);
char *cddb_genre(enum cd_cddb_genre_t genre);

int cddb_direct_mc_alloc(struct disc_mc_data *data, int tracks);
int cddb_mc_alloc(int cd_desc, struct disc_mc_data *data);
void cddb_mc_free(struct disc_mc_data *data);
int cddb_mc_copy_from_data(struct disc_mc_data *outdata,
			   struct disc_data *indata);
int cddb_data_copy_from_mc(struct disc_data *outdata,
			   struct disc_mc_data *indata);

int cddb_connect(struct cddb_server *server);
int cddb_connect_server(struct cddb_host host,
			struct cddb_server *proxy,
			struct cddb_hello hello, ...);
int cddb_skip_http_header(int sock);
int cddb_read_token(int sock, int token[3]);
int cddb_query(int cd_desc, int sock, enum cd_connection_mode_t mode,
	       struct cddb_query *query, ...);
int cddb_read(int cd_desc, int sock, enum cd_connection_mode_t mode,
	      struct cddb_entry entry, struct disc_data *data, ...);
int cddb_quit(int sock);
int cddb_sites(int sock, enum cd_connection_mode_t mode,
	       struct cddb_serverlist *list, ...);

int cddb_read_data(int desc, struct disc_data *data);
int cddb_generate_unknown_entry(int cd_desc, struct disc_data *data);
int cddb_read_disc_data(int cd_desc, struct disc_data *data);
int cddb_write_data(int cd_desc, struct disc_data *data);
int cddb_erase_data(struct disc_data *data);
int cddb_stat_disc_data(int cd_desc, struct cddb_entry *entry);

int cddb_http_query(int cd_desc, struct cddb_host host,
		    struct cddb_hello hello, struct cddb_query *query);
int cddb_http_proxy_query(int cd_desc, struct cddb_host host,
			  struct cddb_server proxy,
			  struct cddb_hello hello,
			  struct cddb_query *query);
int cddb_http_read(int cd_desc, struct cddb_host host,
		   struct cddb_hello hello,
		   struct cddb_entry entry,
		   struct disc_data *data);
int cddb_http_proxy_read(int cd_desc, struct cddb_host host,
			 struct cddb_server proxy,
			 struct cddb_hello hello,
			 struct cddb_entry entry,
			 struct disc_data *data);
int cddb_http_sites(int cd_desc, struct cddb_host host,
		    struct cddb_hello hello,
		    struct cddb_serverlist *list);
int cddb_http_proxy_sites(int cd_desc, struct cddb_host host,
			  struct cddb_server proxy,
			  struct cddb_hello hello,
			  struct cddb_serverlist *list);
int cddb_http_submit(int cd_desc, struct cddb_host host,
		     struct cddb_server *proxy,
		     char *email_address);

int cdindex_discid(int cd_desc, char *discid, int len);

int cdindex_connect_server(struct cddb_host host,
			   struct cddb_server *proxy,
			   char *http_string,
			   int len);
int cdindex_read(int cd_desc, int sock, struct disc_data *data,
		 char *http_string);

int cdindex_write_data(int cd_desc, struct disc_data *data);

int coverart_connect_server(struct cddb_host host,
			    struct cddb_server *proxy,
			    char *http_string,
			    int len);
int coverart_query(int cd_desc, int sock,
		   struct art_query *query,
		   char *http_string);
int coverart_name_query(int sock, struct art_query *query,
			char *http_string, char *album, char *artist);

int coverart_read(struct art_data *art,
		  struct cddb_server *proxy,
		  struct cddb_host host);
int coverart_read_data(int cd_desc, struct art_data *art);
int coverart_write_data(int cd_desc, struct art_data art);

int cd_changer_select_disc(int cd_desc, int disc);
int cd_changer_slots(int cd_desc);
int cd_changer_stat(int cd_desc, struct disc_changer *changer);

#ifdef __cplusplus
}
#endif

#endif
