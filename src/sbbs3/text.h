/* text.h */

/* Synchronet static text string constants */

/****************************************************************************/
/* Macros for elements of the array of pointers (text[]) to static text		*/
/* Auto-generated from CTRL\TEXT.DAT										*/
/****************************************************************************/

#ifndef _TEXT_H
#define _TEXT_H

enum {
	 MsgSubj
	,MsgAttr
	,MsgTo
	,MsgToExt
	,MsgToNet
	,MsgFrom
	,MsgFromExt
	,MsgFromNet
	,MsgDate
	,Email
	,Post
	,TooManyEmailsToday
	,TooManyPostsToday
	,CantAddToQueue
	,R_Email
	,R_Post
	,R_Feedback
	,Emailing
	,Posting
	,NewFile
	,SubjectPrompt
	,EnterMsgNow
	,EnterMsgNowRaw
	,NoMoreLines
	,OnlyNLinesLeft
	,OutOfBytes
	,InvalidLineNumber
	,MsgCleared
	,WithLineNumbersQ
	,Aborted
	,AnonymousQ
	,Anonymous
	,Saving
	,SavedNBytes
	,WritingIndx
	,Emailed
	,Posted
	,EmailNodeMsg
	,R_Forward
	,ForwardedFrom
	,Forwarded
	,AutoMsgBy
	,AutoMsg
	,R_AutoMsg
	,NoMailWaiting
	,MailWaitingLstHdr
	,MailWaitingLstFmt
	,StartWithN
	,ReadingMail
	,CantReplyToMsg
	,Regarding
	,RegardingByOn
	,RegardingByToOn
	,DeleteMailQ
	,OK
	,ForwardMailTo
	,SaveMsgToFile
	,FileToWriteTo
	,NoMailSent
	,MailSentLstHdr
	,ReadingSentMail
	,InternetMailing
	,NoMailOnSystem
	,ReadingAllMail
	,MailOnSystemLstHdr
	,MailOnSystemLstFmt
	,NScanStatusFmt
	,SearchSubFmt
	,NoMsgsOnSub
	,ZScanPostHdr
	,ReadingSub
	,YouDidntPostMsgN
	,DeletePostQ
	,UserDefaultsAutoLogon
	,MsgSentToUser
	,SearchStringPrompt
	,PrivateChatSeparator
	,SubMsgLstFmt
	,SysopChatSeparator
	,NoTextSections
	,TextSectionLstHdr
	,TextSectionLstFmt
	,WhichTextSection
	,TextFilesLstHdr
	,TextFilesLstFmt
	,WhichTextFileSysop
	,WhichTextFile
	,AddTextFileBeforeWhich
	,AddTextFilePath
	,AddTextFileDesc
	,RemoveWhichTextFile
	,DeleteTextFileQ
	,EditWhichTextFile
	,NScanAllGrpsQ
	,SScanAllGrpsQ
	,AreYouSureQ
	,R_Chat
	,ReFeedback
	,SiHdr
	,SiSysName
	,SiSysID
	,SiSysFaddr
	,SiSysPsite
	,SiSysLocation
	,SiSysop
	,SiSysNodes
	,SiNodeNumberName
	,SiNodePhone
	,SiTotalLogons
	,SiLogonsToday
	,SiTotalTime
	,SiTimeToday
	,ViewSysInfoFileQ
	,ViewLogonMsgQ
	,R_ReadSentMail
	,MessageScan
	,MessageScanComplete
	,MessageScanAborted
	,LogOffQ
	,CantPostOnSub
	,SendingMessageToUser
	,NoOtherActiveNodes
	,R_ExternalPrograms
	,UserStats
	,SubLstHdr
	,SubLstFmt
	,GrpLstHdr
	,GrpLstFmt
	,NScanCfgWhichGrp
	,SScanCfgWhichGrp
	,CfgSubLstHdr
	,CfgSubLstFmt
	,CfgGrpLstHdr
	,CfgGrpLstFmt
	,NScanCfgWhichSub
	,SScanCfgWhichSub
	,SubPtrLstFmt
	,WhichOrAll
	,RawMsgInputModeIsNow
	,OFF
	,ON
	,PagingUser
	,SystemStatsHdr
	,NodeStatsHdr
	,StatsTotalLogons
	,StatsLogonsToday
	,StatsTotalTime
	,StatsTimeToday
	,StatsUploadsToday
	,StatsDownloadsToday
	,StatsPostsToday
	,StatsEmailsToday
	,StatsFeedbacksToday
	,ChUserPrompt
	,ChUserPwPrompt
	,CommaInLocationRequired
	,ErrorLogHdr
	,DeleteErrorLogQ
	,DirectoryDoesNotExist
	,ClearErrCounter
	,InvalidNode
	,SendingTelegramToUser
	,DeleteGuruLogQ
	,TelegramFmt
	,R_Download
	,SearchingAllDirs
	,SearchingAllLibs
	,NFilesListed
	,EmptyDir
	,NScanHdr
	,R_RemoveFiles
	,DirFull
	,R_Upload
	,CantUploadHere
	,FileSpec
	,SystemPassword
	,NoSysopDir
	,CantUploadToSysop
	,DirLstHdr
	,DirLstFmt
	,LibLstHdr
	,LibLstFmt
	,InvalidNetMailAddr
	,TransferPolicyHdr
	,TransferProtLstFmt
	,TpUpload
	,TpDownload
	,NoUserDir
	,NoFilesForYou
	,UserDirFull
	,CantUploadToUser
	,BoxHdrLib
	,BoxHdrDir
	,BoxHdrFiles
	,ShortHdrLib
	,ShortHdrDir
	,BatchDlFlags
	,BatchDlQueueIsFull
	,FileSpecStarDotStar
	,LowDiskSpace
	,DiskNBytesFree
	,Filename
	,BadFilename
	,UploadToSysopDirQ
	,UploadToUserDirQ
	,UploadToCurDirQ
	,FileAlreadyThere
	,FileOnDiskAddQ
	,FileNotOnDisk
	,TheseFileExtsOnly
	,FileAlreadyOnline
	,EnterAfterLastDestUser
	,SendFileToUser
	,DuplicateUser
	,UserWontBeAbleToDl
	,CantSendYourselfFiles
	,UserAddedToDestList
	,RateThisFile
	,Rated
	,MultipleDiskQ
	,HowManyDisksTotal
	,NumberOfFile
	,FileOneOfTen
	,FileOneOfTwo
	,EnterDescNow
	,NoDescription
	,ProtocolOrQuit
	,ProtocolBatchOrQuit
	,BatchUlQueueIsFull
	,FileAddedToUlQueue
	,UserToUserXferNodeMsg
	,FileInfoPrompt
	,QuitOrNext
	,RExemptRemoveFilePrompt
	,MoveToLibLstFmt
	,MoveToLibPrompt
	,MoveToDirLstFmt
	,MoveToDirPrompt
	,MovedFile
	,CloseFileRecordQ
	,SysopRemoveFilePrompt
	,UserRemoveFilePrompt
	,FileDoesNotExist
	,CouldntRemoveFile
	,DeleteFileQ
	,AddToOfflineDirQ
	,RemoveCreditsQ
	,UserNotFound
	,CreditsToRemove
	,FileRemovedUserMsg
	,EditFilename
	,CouldntRenameFile
	,FileRenamed
	,EditDescription
	,DeleteExtDescriptionQ
	,EditUploader
	,EditCreditValue
	,EditTimesDownloaded
	,EditOpenCount
	,EditAltPath
	,YouOnlyHaveNCredits
	,NotEnoughCredits
	,NotEnoughTimeToDl
	,ProtocolBatchQuitOrNext
	,BulkUpload
	,BulkUploadDescPrompt
	,NoFilesInBatchQueue
	,BatchMenuPrompt
	,ClearUploadQueueQ
	,UploadQueueCleared
	,ClearDownloadQueueQ
	,DownloadQueueCleared
	,DownloadQueueIsEmpty
	,UploadQueueLstHdr
	,UploadQueueLstFmt
	,DownloadQueueLstHdr
	,DownloadQueueLstFmt
	,DownloadQueueTotals
	,RemoveWhichFromUlQueue
	,RemoveWhichFromDlQueue
	,UploadQueueIsEmpty
	,HangUpAfterXferQ
	,StartXferNow
	,Disconnecting
	,Disconnected
	,FileNotSent
	,RemovingTempFiles
	,ExtractFrom
	,UnextractableFile
	,FileNotFound
	,ExtractFilesPrompt
	,TempDirPrompt
	,TempFileNotCreatedYet
	,TempFileInfo
	,TempDirTotal
	,NFilesRemoved
	,ResortWarning
	,ResortLineFmt
	,ResortEmptyDir
	,Sorting
	,Sorted
	,Compressed
	,FileAlreadyInQueue
	,FileIsNotOnline
	,FileAddedToBatDlQueue
	,NonviewableFile
	,FileNotReceived
	,FileHadErrors
	,FileZeroLength
	,FileNBytesReceived
	,FileNBytesSent
	,DownloadUserMsg
	,Partially
	,FiLib
	,FiDir
	,FiFilename
	,FiFileSize
	,FiCredits
	,FiDescription
	,FiUploadedBy
	,FiFileDate
	,FiDateUled
	,FiDateDled
	,FiTimesDled
	,FiTransferTime
	,FiAlternatePath
	,InvalidAlternatePathN
	,FileIsOpen
	,HappyBirthday
	,TimeToChangePw
	,NewPasswordQ
	,NewPassword
	,VerifyPassword
	,Wrong
	,PasswordChanged
	,NoMoreLogons
	,R_Logons
	,EnterYourAlias
	,EnterYourRealName
	,EnterYourCompany
	,EnterYourHandle
	,EnterYourSex
	,EnterYourAddress
	,EnterYourPhoneNumber
	,EnterYourBirthday
	,EnterYourCityState
	,EnterYourZipCode
	,EnterYourComputer
	,CallingFromNorthAmericaQ
	,UserInfoCorrectQ
	,LiUserNumberName
	,LiLogonsToday
	,LiTimeonToday
	,LiMailWaiting
	,LiSysopIs
	,LiSysopAvailable
	,LiSysopNotAvailable
	,UserOnTwoNodes
	,CriticalErrors
	,UserXferForYou
	,UnreceivedUserXfer
	,ReadYourMailNowQ
	,NoNewUsers
	,NewUserPasswordPrompt
	,AutoTerminalQ
	,AnsiTerminalQ
	,ColorTerminalQ
	,RipTerminalQ
	,ExAsciiTerminalQ
	,YouCantUseThatName
	,YourPasswordIs
	,NewUserPasswordVerify
	,IncorrectPassword
	,MagicWordPrompt
	,FailedMagicWord
	,SystemFull
	,NewUserFeedbackHdr
	,NoFeedbackWarning
	,NoXtrnPrograms
	,XtrnProgLstHdr
	,XtrnProgLstTitles
	,XtrnProgLstUnderline
	,XtrnProgLstFmt
	,WhichXtrnProg
	,UserRunningXtrn
	,RemoveNodeLockQ
	,MinimumModemSpeed
	,NoNodeAccess
	,NodeLocked
	,UnknownUser
	,InvalidLogon
	,SlogFmt
	,Locally
	,SortAlphaQ
	,CheckingSlots
	,UserListFmt
	,NTotalUsers
	,NUsersOnCurSub
	,NUsersOnCurDir
	,NScanDate
	,NScanYear
	,NScanMonth
	,NScanDay
	,NScanHour
	,NScanMinute
	,NScanPmQ
	,NScanAmQ
	,PasswordTooShort
	,PasswordNotChanged
	,PasswordInvalid
	,PasswordObvious
	,ComputerTypeMenu
	,ComputerTypePrompt
	,ComputerTypeB
	,ComputerTypeC
	,ComputerTypeD
	,ComputerTypeE
	,NoUserData
	,Deleted
	,Inactive
	,UeditAliasPassword
	,UeditRealNamePhone
	,UeditAddressBirthday
	,UeditLocationZipcode
	,UeditNoteHandle
	,UeditComputerModem
	,UeditCommentLine
	,UserDates
	,UserTimes
	,UserLogons
	,UserEmails
	,UserNetMail
	,UserUploads
	,UserDownloads
	,UserLeech
	,UserCredits
	,UserMinutes
	,UeditSecLevel
	,UeditFlags
	,UeditExempts
	,UeditPrompt
	,UeditRestoreQ
	,UeditActivateQ
	,UeditDeleteQ
	,UeditReadUserMailWQ
	,UeditReadUserMailSQ
	,UeditDeactivateUserQ
	,ChangeExemptionQ
	,FlagEditing
	,GoToUser
	,UeditLastOn
	,UeditFirstOn
	,UeditExpire
	,UeditPwModDate
	,UeditML
	,UeditNote
	,UeditComment
	,UeditUlBytes
	,UeditUploads
	,UeditDlBytes
	,UeditDownloads
	,UeditLeech
	,QuickValidateFmt
	,QuickValidatePrompt
	,UeditPassword
	,UeditCredits
	,UeditMinutes
	,UeditCopyUserQ
	,UeditCopyUserToSlot
	,ChangeRestrictsQ
	,ModifyCredits
	,ModifyMinutes
	,DeleteQuestionaireQ
	,UserDefaultsHdr
	,UserDefaultsTerminal
	,UserDefaultsXeditor
	,UserDefaultsRows
	,UserDefaultsMenuMode
	,UserDefaultsPause
	,UserDefaultsHotKey
	,UserDefaultsCursor
	,UserDefaultsCLS
	,UserDefaultsAskNScan
	,UserDefaultsAskSScan
	,UserDefaultsANFS
	,UserDefaultsRemember
	,UserDefaultsBatFlag
	,UserDefaultsNetMail
	,UserDefaultsCommandSet
	,UserDefaultsQuiet
	,UserDefaultsPassword
	,UserDefaultsArcType
	,UserDefaultsProtocol
	,UserDefaultsWhich
	,On
	,Off
	,HowManyRows
	,CurrentPassword
	,ForwardMailQ
	,EnterNetMailAddress
	,SelectItemHdr
	,SelectItemFmt
	,SelectItemWhich
	,SysopIsHere
	,EndOfChat
	,ChatPrompt
	,AnonUserChatHandle
	,WelcomeToMultiChat
	,WelcomeToChannelN
	,NodeInMultiChatLocally
	,YoureOnTheAir
	,NodeJoinedMultiChat
	,NodeLeftMultiChat
	,MultiChatCommandPrompt
	,PasswordProtected
	,CorrectPassword
	,WrongPassword
	,PasswordProtectChanQ
	,PasswordPrompt
	,ChatLineFmt
	,SysopPageIsNow
	,SysopIsNotAvailable
	,ChatWithGuruInsteadQ
	,PrivateMsgPrompt
	,NodeToPrivateChat
	,NodeNAlreadyInPChat
	,NodeNIsNotInUse
	,NoNeedToPageSelf
	,CantPageNode
	,NodePageMsg
	,AllNodePageMsg
	,NodePChatPageMsg
	,R_SendMessages
	,NodeToSendMsgTo
	,NoNeedToSendMsgToSelf
	,NodeMsgPrompt
	,NodeMsgFmt
	,AllNodeMsgFmt
	,PagingGuru
	,WaitingForNodeInPChat
	,NodeJoinedPrivateChat
	,NodeLeftPrivateChat
	,NoOneHasLoggedOnToday
	,Unused544 /* Was LastFewCallers */
	,LastFewCallersFmt
	,CallersToday
	,DoYouMeanThisUserQ
	,UNKNOWN_USER
	,TimesUp
	,NodeLoggedOff
	,NodeLoggedOnAtNbps
	,TiLogon
	,TiNow
	,TiTimeon
	,TiTimeLeft
	,ControlKeyMenu
	,TakenTooLongToLogon
	,CallBackWhenYoureThere
	,YesNoQuestion
	,Yes
	,No
	,NoYesQuestion
	,Pause
	,ContinueQ /* was Wait */
	,SysStatsLogHdr
	,NodeStatsLogHdr
	,ReducedTime
	,EventInfo
	,UploadBeforeEvent
	,QWKPrompt
	,QWKCtrlACodes
	,QWKPackingSubboard
	,QWKPackedSubboard
	,QWKPackingEmail
	,QWKPackedEmail
	,QWKUnpacking
	,QWKUnpacked
	,QWKNoNewMessages
	,QWKCompressionFailed
	,QWKExtractionFailed
	,QWKReplyNotReceived
	,QWKInvalidConferenceN
	,CreatingFileList
	,CreatedFileList
	,NoFiles
	,MsgPtrsInitialized
	,ConversionRate
	,CreditsToMin
	,YouHaveTooManyMinutes
	,BillingNodeMsg
	,Convert100ktoNminQ
	,CreditedAccount
	,ANSICaptureIsNow
	,RetrievingFile
	,AltULPathIsNow
	,PrivatePostQ
	,PostTo
	,NoToUser
	,UsingRealName
	,PostingPrivately
	,PostingAnonymously
	,CantDeletePosts
	,SubInfoHdr
	,SubInfoLongName
	,SubInfoShortName
	,SubInfoQWKName
	,SubInfoMaxMsgs
	,SubInfoTagLine
	,SubInfoFidoNet
	,SubInfoViewFileQ
	,DirInfoHdr
	,DirInfoLongName
	,DirInfoShortName
	,DirInfoAllowedExts
	,DirInfoMaxFiles
	,DirInfoViewFileQ
	,NoNetMailAllowed
	,NetMailCostContinueQ
	,NetMailing
	,RemoveFromNewScanQ
	,SubGroupOrAll
	,DirLibOrAll
	,EnterPath
	,SearchExtendedQ
	,DisplaySubjectsOnlyQ
	,EchoIsNow
	,WelcomeToPrivateChat
	,UploadingREP
	,ReceivedFileViaQWK
	,QWKmsgLimitReached
	,PrivatePostsNotAllowed
	,LoadingMsgPtrs
	,LoadedMsgPtrs
	,QuoteMessageQ
	,QuoteLinesPrompt
	,ChatChanLstHdr
	,ChatChanLstTitles
	,ChatChanLstUnderline
	,ChatChanLstFmt
	,CantAccessThatChannel
	,CantDownloadFromDir
	,SearchingForDupes
	,SearchedForDupes
	,AccountWillExpireInNDays
	,AccountHasExpired
	,DownloadBatchQ
	,WaitingForDeviceN
	,UserSentYouMail
	,UserSentYouFile
	,UserReadYourMail
	,UserReadYourMailNodeMsg
	,JoinWhichGrp
	,JoinWhichSub
	,JoinWhichLib
	,JoinWhichDir
	,CfgDirLstHdr
	,CfgDirLstFmt
	,CfgLibLstHdr
	,CfgLibLstFmt
	,BatchFlagPrompt
	,FileListBatchCommands
	,DownloadAttachedFileQ
	,FreeMinLeft
	,FreeMinToDeposit
	,EmailFilesNotAllowed
	,CantRunThatProgram
	,OnlyXminutesLeft
	,AreYouThere
	,NoAccessLevel
	,NoAccessAge
	,NoAccessBPS
	,NoAccessCredit
	,NoAccessNode
	,NoAccessUser
	,NoAccessExpire
	,NoAccessTimeLeft
	,NoAccessTimeUsed
	,NoAccessTime
	,NoAccessPCR
	,NoAccessUDR
	,NoAccessUDFR
	,NoAccessFlag1
	,NoAccessFlag2
	,NoAccessFlag3
	,NoAccessFlag4
	,NoAccessSex
	,NoAccessExempt
	,NoAccessRest
	,NoAccessDay
	,NoAccessGroup
	,NoAccessSub
	,NoAccessLib
	,NoAccessDir
	,NodeLstHdr
	,NodeActionMain
	,NodeActionReadMsgs
	,NodeActionReadMail
	,NodeActionSendMail
	,NodeActionReadTxt
	,NodeActionReadSentMail
	,NodeActionPostMsg
	,NodeActionAutoMsg
	,NodeActionXtrn
	,NodeActionDefaults
	,NodeActionXfer
	,NodeActionDLing
	,NodeActionULing
	,NodeActionBiXfer
	,NodeActionListFiles
	,NodeActionLoggingOn
	,NodeActionLocalChat
	,NodeActionMultiChat
	,NodeActionGuruChat
	,NodeActionChatSec
	,NodeActionSysopAct
	,NodeActionQWK
	,NodeActionPrivateChat
	,NodeActionPaging
	,NodeActionRetrieving
	,YNQP /* (Yes/No/Quit/Password chars) */
	,ViewSignatureQ
	,DeleteSignatureQ
	,CreateEditSignatureQ
	,SpinningCursorOnPauseQ
	,UseExternalEditorQ
	,ExternalEditorHeading
	,CommandShellHeading
	,ArchiveTypeHeading
	,ValidatePostQ
	,NodeStatusWaitingForCall
	,NodeStatusLogon
	,NodeStatusNewUser
	,NodeStatusOffline
	,NodeStatusEventWaiting
	,NodeStatusEventRunning
	,NodeStatusEventLimbo
	,NodeConnectionTelnet
	,NodeConnectionRLogin
	,NodeConnectionSSH
	,NodeConnectionModem
	,QWKSettingsHdr
	,QWKSettingsCtrlA
	,QWKSettingsArchive
	,QWKSettingsEmail
	,QWKSettingsAttach
	,QWKSettingsDeleteEmail
	,QWKSettingsNewFilesList
	,QWKSettingsIndex
	,QWKSettingsControl
	,QWKSettingsHeaders
	,QWKSettingsBySelf
	,QWKSettingsTimeZone
	,QWKSettingsVIA
	,QWKSettingsMsgID
	,QWKSettingsExtended
	,QWKSettingsWhich
	,CantEditMsg
	,CantDeleteMsg
	,CantReadSub
	,CantPostMsg
	,OperatorPrompt
	,AddSubToNewScanQ
	,UnvalidatedWarning
	,StartingNewUserRegistration
	,GetStrMenu
	,DisplayUnreadMessagesOnlyQ
	,NoMessagesFound
	,UserIpAddr
	,Seconds
	,Minutes
	,Hours
	,Days
	,Months
	,Years
	,InThePast
	,InTheFuture
	,AgeOfPostedItem
	,NodeStatusLogout
	,VotingNotAllowed
	,VotedAlready
	,R_Voting
	,QWKSettingsVoting
	,VoteMsgUpDownOrQuit
	,MsgVotes
	,MsgUpVoteNotice
	,MsgDownVoteNotice
	,PollVoteNotice
	,PollAnswerNumber
	,PollAnswerFmt
	,PollAnswerChecked
	,BallotHdr
	,BallotAnswerFmt
	,BallotVoteWhich
	,Only
	,SPAMVisibilityIsNow
	,VoteInThisPollNow
	,MIMEDecodedPlainText
	,MsgHdrBodySeparator
	,FileHdrDescSeparator
	,RemoveFileQ
	,OriginFidoAddr
	,VoteNoticeFmt
	,TagMessageQ
	,TagMessagePrompt
	,MsgTags
	,NoAccessTerminal
	,LongLineContinuationPrefix
	,Scanning
	,Done
	,Scanned
	,HitYourBackspaceKey
	,CharacterReceivedFmt
	,InvalidBackspaceKeyFmt
	,SwapDeleteKeyQ
	,PetTermDetected

	,TOTAL_TEXT
};

#endif
