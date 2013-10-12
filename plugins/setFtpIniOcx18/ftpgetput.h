#ifdef __cplusplus
extern "C" {
#endif

	enum FTP_ERROR
	{
		FTP_UNKNOW,
		FTP_PARAM_INVALID,
		FTP_CONN_FAILURE,
		FTP_UPLOAD_SUCCESS,
		FTP_UPLOAD_FAIL,
		FTP_PASS_FAIL,
		FTP_NAME_INVALID,
		FTP_END,
	};

/**下载一个文件从ftpserer , 
pcServerFileName  为   
       /摄像头名/LightConfig.txt  服务器目录
pcLocalFile    .\\LightConfig.txt
**/

int ftpgetfile(char*  pcServerIP,
			   int    nServerPort,
			   char*  pcUserName,
			   char*  pcUserPass,
			   char*  pcServerFileName,
			   char*  pcLocalFile);


/**上传 一个文件从ftpserer , 
pcServerFileName  为   
       /摄像头名/LightConfig.txt  服务器目录
pcLocalFile    .\\LightConfig.txt
**/
int ftpputfile(char*  pcServerIP,
			   int    nServerPort,
			   char*  pcUserName,
				char*  pcUserPass,
				char*  pcLocalFile,
				char*  pcServerName);


/** 应用配置
**/

int  ftpconfirm(char*  pcServerIP,
				int    nServerPort,
				char*  pcUserName,
				char*  pcUserPass, 
				char*  pCameraName);


int  ftplock(char*  pcServerIP,
			 int    nServerPort,
			 char*  pcUserName,
			 char*  pcUserPass,
			 char*  pcCamera,
			 BOOL   isLock);

#ifdef __cplusplus
};
#endif