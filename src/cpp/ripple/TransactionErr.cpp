#include "TransactionErr.h"
#include "utils.h"

bool transResultInfo(TER terCode, std::string& strToken, std::string& strHuman)
{
	static struct {
		TER				terCode;
		const char*		cpToken;
		const char*		cpHuman;
	} transResultInfoA[] = {
		{	tecCLAIM,				"tecCLAIM",					"Fee claimed. Sequence used. No action."				},
		{	tecDIR_FULL,			"tecDIR_FULL",				"Can not add entry to full directory."					},
		{	tecINSUF_RESERVE_LINE,	"tecINSUF_RESERVE_LINE",	"Insufficent reserve to add trust line."				},
		{	tecINSUF_RESERVE_OFFER,	"tecINSUF_RESERVE_OFFER",	"Insufficent reserve to create offer."					},
		{	tecNO_DST,				"tecNO_DST",				"Destination does not exist. Send XRP to create it."	},
		{	tecNO_DST_INSUF_XRP,	"tecNO_DST_INSUF_XRP",		"Destination does not exist. Too little XRP sent to create it."		},
		{	tecNO_LINE_INSUF_RESERVE,	"tecNO_LINE_INSUF_RESERVE",	"No such line. Too little reserve to create it."	},
		{	tecNO_LINE_REDUNDANT,	"tecNO_LINE_REDUNDANT",		"Can't set non-existant line to default."				},
		{	tecPATH_DRY,			"tecPATH_DRY",				"Path could not send partial amount."					},
		{	tecPATH_PARTIAL,		"tecPATH_PARTIAL",			"Path could not send full amount."						},

		{	tecUNFUNDED,			"tecUNFUNDED",				"Source account had insufficient balance for transaction."	},

		{	tefFAILURE,				"tefFAILURE",				"Failed to apply."										},
		{	tefALREADY,				"tefALREADY",				"The exact transaction was already in this ledger."		},
		{	tefBAD_ADD_AUTH,		"tefBAD_ADD_AUTH",			"Not authorized to add account."						},
		{	tefBAD_AUTH,			"tefBAD_AUTH",				"Transaction's public key is not authorized."			},
		{	tefBAD_CLAIM_ID,		"tefBAD_CLAIM_ID",			"Malformed: Bad claim id."								},
		{	tefBAD_GEN_AUTH,		"tefBAD_GEN_AUTH",			"Not authorized to claim generator."					},
		{	tefBAD_LEDGER,			"tefBAD_LEDGER",			"Ledger in unexpected state."							},
		{	tefCLAIMED,				"tefCLAIMED",				"Can not claim a previously claimed account."			},
		{	tefEXCEPTION,			"tefEXCEPTION",				"Unexpected program state."								},
		{	tefCREATED,				"tefCREATED",				"Can't add an already created account."					},
		{	tefGEN_IN_USE,			"tefGEN_IN_USE",			"Generator already in use."								},
		{	tefPAST_SEQ,			"tefPAST_SEQ",				"This sequence number has already past."				},

		{	telLOCAL_ERROR,			"telLOCAL_ERROR",			"Local failure."										},
		{	telBAD_PATH_COUNT,		"telBAD_PATH_COUNT",		"Malformed: Too many paths."							},
		{	telINSUF_FEE_P,			"telINSUF_FEE_P",			"Fee insufficient."										},

		{	temMALFORMED,			"temMALFORMED",				"Malformed transaction."								},
		{	temBAD_AMOUNT,			"temBAD_AMOUNT",			"Can only send positive amounts."						},
		{	temBAD_AUTH_MASTER,		"temBAD_AUTH_MASTER",		"Auth for unclaimed account needs correct master key."	},
		{	temBAD_FEE,				"temBAD_FEE",				"Invalid fee, negative or not XRP."						},
		{	temBAD_EXPIRATION,		"temBAD_EXPIRATION",		"Malformed: Bad expiration."							},
		{	temBAD_ISSUER,			"temBAD_ISSUER",			"Malformed: Bad issuer."								},
		{	temBAD_LIMIT,			"temBAD_LIMIT",				"Limits must be non-negative."							},
		{	temBAD_OFFER,			"temBAD_OFFER",				"Malformed: Bad offer."									},
		{	temBAD_PATH,			"temBAD_PATH",				"Malformed: Bad path."									},
		{	temBAD_PATH_LOOP,		"temBAD_PATH_LOOP",			"Malformed: Loop in path."								},
		{	temBAD_PUBLISH,			"temBAD_PUBLISH",			"Malformed: Bad publish."								},
		{	temBAD_TRANSFER_RATE,	"temBAD_TRANSFER_RATE",		"Malformed: Transfer rate must be >= 1.0"				},
		{	temBAD_SEQUENCE,		"temBAD_SEQUENCE",			"Malformed: Sequence is not in the past."				},
		{	temDST_IS_SRC,			"temDST_IS_SRC",			"Destination may not be source."						},
		{	temDST_NEEDED,			"temDST_NEEDED",			"Destination not specified."							},
		{	temINVALID,				"temINVALID",				"The transaction is ill-formed."						},
		{	temINVALID_FLAG,		"temINVALID_FLAG",			"The transaction has an invalid flag."					},
		{	temREDUNDANT,			"temREDUNDANT",				"Sends same currency to self."							},
		{	temRIPPLE_EMPTY,		"temRIPPLE_EMPTY",			"PathSet with no paths."								},
		{	temUNCERTAIN,			"temUNCERTAIN",				"In process of determining result. Never returned."		},
		{	temUNKNOWN,				"temUNKNOWN",				"The transactions requires logic not implemented yet."	},

		{	terRETRY,				"terRETRY",					"Retry transaction."									},
		{	terFUNDS_SPENT,			"terFUNDS_SPENT",			"Can't set password, password set funds already spent."	},
		{	terINSUF_FEE_B,			"terINSUF_FEE_B",			"Account balance can't pay fee."						},
		{	terNO_ACCOUNT,			"terNO_ACCOUNT",			"The source account does not exist."					},
		{	terNO_LINE,				"terNO_LINE",				"No such line."											},
		{	terPRE_SEQ,				"terPRE_SEQ",				"Missing/inapplicable prior transaction."				},

		{	tesSUCCESS,				"tesSUCCESS",				"The transaction was applied."							},
	};

	int	iIndex	= NUMBER(transResultInfoA);

	while (iIndex-- && transResultInfoA[iIndex].terCode != terCode)
		;

	if (iIndex >= 0)
	{
		strToken	= transResultInfoA[iIndex].cpToken;
		strHuman	= transResultInfoA[iIndex].cpHuman;
	}

	return iIndex >= 0;
}

std::string transToken(TER terCode)
{
	std::string	strToken;
	std::string	strHuman;

	return transResultInfo(terCode, strToken, strHuman) ? strToken : "-";
}

std::string transHuman(TER terCode)
{
	std::string	strToken;
	std::string	strHuman;

	return transResultInfo(terCode, strToken, strHuman) ? strHuman : "-";
}

// vim:ts=4
