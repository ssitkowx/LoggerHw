///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include "LoggerMock.h"
#include "LoggerFixture.hxx"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEST_F (LoggerFixture, ManuallyCheckLogColorAndCorrectDisplay)
{
    LOGW        (MODULE, "ManuallyCheckLogColorAndCorrectDisplay");

    LOG         (MODULE, "Test common log."    , "Iteration number: ", ONE);
    LOGE        (MODULE, "Test log error"      , "Iteration number: ", TWO);
    LOGI        (MODULE, "Test log information", "Iteration number: ", THREE);
    LOGD        (MODULE, "Test log debug"      , "Iteration number: ", FOUR);
    LOGV        (MODULE, "Test log verbose"    , "Iteration number: ", FIVE);
    LOGW        (MODULE, "Test log warning"    , "Iteration number: ", SIX);
    EXPECT_TRUE (true);
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////