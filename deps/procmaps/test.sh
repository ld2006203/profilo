#!/bin/sh
rt() {
    ./procmaps-test 1 test.maps "$@"
}

echo @@ Maps
rt

echo @@ Expected success
rt 0000000000400000
rt 00000000006ef000
rt 00000000006f0000
rt 00000000006f9000
rt 00000000017a9000
rt 00007fbca87c9000
rt 00007fbca87d4000
rt 00007fbca89d3000
rt 00007fbca89d4000
rt 00007fbca89d5000
rt 00007fbca89e0000
rt 00007fbca8bdf000
rt 00007fbca8be0000
rt 00007fbca8be1000
rt 00007fbca8bf8000
rt 00007fbca8df7000
rt 00007fbca8df8000
rt 00007fbca8df9000
rt 00007fbca8dfb000
rt 00007fbca8e04000
rt 00007fbca9003000
rt 00007fbca9004000
rt 00007fbca9005000
rt 00007fbca92ce000
rt 00007fbca9489000
rt 00007fbca9689000
rt 00007fbca968d000
rt 00007fbca968f000
rt 00007fbca9694000
rt 00007fbca9697000
rt 00007fbca9896000
rt 00007fbca9897000
rt 00007fbca9898000
rt 00007fbca98bd000
rt 00007fbca9abc000
rt 00007fbca9ac0000
rt 00007fbca9ac1000
rt 00007fbca9cb3000
rt 00007fbca9cda000
rt 00007fbca9ce1000
rt 00007fbca9ce3000
rt 00007fbca9ce4000
rt 00007fbca9ce5000
rt 00007fff944b0000
rt 00007fff945fe000
rt ffffffffff600000
rt 00007fbca968d005

echo @@ Expected failure
rt 0
rt 1
rt ffffffffffffffff
rt 00007fbca9cb6000
rt deadf00ddeadf00d