. ./utils.sh

subtitle "test TOPIC"

sh ./test_TOPIC/test_err_403.sh
# sh ./test_TOPIC/test_err_442.sh
sh ./test_TOPIC/test_err_451.sh
sh ./test_TOPIC/test_err_461.sh
sh ./test_TOPIC/test_err_482.sh
sh ./test_TOPIC/test_ok.sh

echo ""
