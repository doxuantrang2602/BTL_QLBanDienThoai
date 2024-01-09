function deleteOrder() {
    if (confirm("Bạn có chắc chắn muốn xóa đơn hàng này không?") == true)
    {
      alert("Xóa đơn hàng thành công!");
      backToList();
    } 
}
function viewOrder() {
    window.location="view-order.html";  
}
function editOrder() {
    window.location="edit-order.html";
}
function backToList() {
    window.location="orders-management.html";
}
function addOrder() {
    window.location="add-order.html";
}

function validatetOrder() {
    let idOrder = document.getElementById("order-id").value.trim();
    let customer = document.getElementById("customer-selection").value;
    let phone = document.getElementById("tel").value.trim();
    let address = document.getElementById("address").value.trim();
    let date = document.getElementById("datetime").value;
    let status = document.getElementById("status-selection").value;
    let numberofproducts = document.getElementById("numberofproducts").value;
    let flag = 1;
    if(idOrder.length == 0) {
        document.getElementById("order-id-error").innerHTML = "Vui lòng nhập mã đơn hàng";
        document.getElementById("order-id-error").style.display = "block";
        document.getElementById("order-id").style.borderColor = "red";
        flag = 0;
    }

    if(customer.length == 0) {
        document.getElementById("customer-selection-error").innerHTML = "Vui lòng chọn khách hàng";
        document.getElementById("customer-selection-error").style.display = "block";
        document.getElementById("customer-selection").style.borderColor = "red";
        flag = 0;
    }

    if(phone.length == 0) {
        document.getElementById("tel-error").innerHTML = "Vui lòng nhập số điện thoại";
        document.getElementById("tel-error").style.display = "block";
        document.getElementById("tel").style.borderColor = "red";
        flag = 0;
    } else if(phone.length != 10 || phone.substr(0,1) != "0" || /[^0-9]/.test(phone) == true)
    {
        document.getElementById("tel-error").innerHTML = "Số điện thoại không hợp lệ. Số điện thoại bao gồm 10 chữ số và bắt đầu bởi số 0.";
        document.getElementById("tel-error").style.display = "block";
        document.getElementById("tel").style.borderColor = "red";
        flag = 0;
    }

    if(address.length == 0) {
        document.getElementById("address-error").innerHTML = "Vui lòng nhập địa chỉ nhận hàng";
        document.getElementById("address-error").style.display = "block";
        document.getElementById("address").style.borderColor = "red";
        flag = 0;
    }

    if(date.length == 0) {
        document.getElementById("datetime-error").innerHTML = "Vui lòng chọn ngày đặt hàng";
        document.getElementById("datetime-error").style.display = "block";
        document.getElementById("datetime").style.borderColor = "red";
        flag = 0;
    }

    if(status.length == 0) {
        document.getElementById("status-error").innerHTML = "Vui lòng chọn trạng thái đơn hàng";
        document.getElementById("status-error").style.display = "block";
        document.getElementById("status-selection").style.borderColor = "red";
        flag = 0;
    }

    if(numberofproducts <= 0 ) {
        document.getElementById("products-selection-error").innerHTML = "Vui lòng chọn sản phẩm";
        document.getElementById("products-selection-error").style.display = "block";
        document.getElementById("products-selection").style.borderColor = "red";
        flag = 0;
    }

    if(flag == 1){
        return true;
    }else{
        return false;
    }
}

function addNewOrder(){
    if(validatetOrder()){
        if(confirm("Thêm mới đơn hàng thành công!\nNhấn OK để tiếp tục thêm mới một đơn hàng khác. Nhấn Hủy để về danh sách."))
        {
            addOrder();
        }else{
            backToList();
        }
    } 
}
function editAnOrder(){
    if(validatetOrder()){
        alert("Sửa đơn hàng thành công");
        backToList();
    } 
}
function chooseProducts(){
    let selectedProduct, selectedProductName, info, oldTableData, newTableData,selectedValue;
    let numberofproducts = document.getElementById("numberofproducts").value;
    selectedProduct = document.getElementById("products-selection");
    let selectedProductList = document.getElementById("selected-products").value;
    selectedValue = selectedProduct.value;
    selectedProductName = selectedProduct.options[selectedProduct.selectedIndex].text;
    info =  selectedValue.split("-");
    if( selectedProductList.search(info[0]) == -1 )
    {
        document.getElementById("selected-products").value =  selectedProductList.concat("|", info[0]);
        oldTableData = document.getElementById("products-table").innerHTML;
        oldTableData = oldTableData.replace('<tbody>','').replace('</tbody>','');
        let price = info[2];
        let formattedPrice = Number(price).toLocaleString() +" đ";
        newTableData = oldTableData + "<tr id ="+info[0]+"><td>"+info[0]+"</td><td>"+selectedProductName+'</td><td id="remaining-'+info[0]+'">'+info[1]+'</td><td id="td-number-'+info[0]+'"><input type="number" id ="number-'+info[0]+'" value ="1" onchange="changeNumberBuy('+"'"+info[0]+"'"+',1);"></td><td id="price-'+info[0]+'">'+formattedPrice+'</td><td id="total-'+info[0]+'">'+formattedPrice+'</td><td><button class="delete-product" onclick="'+'deleteProduct('+"'"+info[0]+"'"+')">Xóa</button></td></tr>';
        document.getElementById("products-table").innerHTML = newTableData;
        oldTableData = newTableData;
        let sum = document.getElementById("sum").innerHTML;
        sum = sum.replace(/\D/g,"");
        let newSum = Number(sum) + Number(price);
        let formattednewSum = newSum.toLocaleString()+" đ";
        document.getElementById("sum").innerHTML = formattednewSum ;
        numberofproducts = Number(numberofproducts) + 1;
        document.getElementById("products-selection").value = "";
        document.getElementById("numberofproducts").value = numberofproducts;
        changeValue("products-selection");
    }
    else {
        alert("Sản phẩm này đã có trên danh sách. Vui lòng thay đổi số lượng mua nếu muốn.");
    }
    
}

function changeNumberBuy(obj,oldValue){
    let idNumber = "number-"+obj;
    let idPrice = "price-"+obj;
    let idTotal = "total-"+obj;
    let idTdNumber = "td-number-"+obj;
    let idRemaining = "remaining-"+obj;
    let number = document.getElementById(idNumber).value;
    let remaining = document.getElementById(idRemaining).innerHTML; 

    if(Number(number) <=0){
        alert("Số lượng mua không được < 0 hoặc để trống.");
        document.getElementById(idNumber).value = oldValue;
    } else if(Number(number) > Number(remaining)){
        alert("Số lượng mua không được lớn hơn tồn kho của sản phẩm.");
        document.getElementById(idNumber).value = oldValue;
    }else{
        let price = document.getElementById(idPrice).innerHTML;
        price = price.replace(/\D/g,"");
        let total = number*price;
        let sum = document.getElementById("sum").innerHTML;
        sum = sum.replace(/\D/g,"");
        sum = Number(sum) + Number(number - oldValue)*price;
        let formattedtotal = total.toLocaleString()+" đ";
        document.getElementById(idTotal).innerHTML = formattedtotal;
        let formattedsum = sum.toLocaleString()+" đ";
        document.getElementById("sum").innerHTML = formattedsum;
        document.getElementById(idTdNumber).innerHTML= '<input type="number" id ="number-'+obj+'" value ="'+number+'" onchange="changeNumberBuy('+"'"+obj+"'"+','+"'"+number+"'"+');">';

    }
    }

function deleteProduct(obj){
    let sum = document.getElementById("sum").innerHTML;
    sum = sum.replace(/\D/g,"");
    let numberofproducts = document.getElementById("numberofproducts").value;
    let idTotal = "total-"+obj;
    let total = document.getElementById(idTotal).innerHTML;
    total = total.replace(/\D/g,"");
    let newSum = Number(sum) - Number(total);
    document.getElementById(obj).remove();
    let formattednewSum = newSum.toLocaleString()+" đ";
    document.getElementById("sum").innerHTML = formattednewSum;
    numberofproducts = Number(numberofproducts) - 1;
    document.getElementById("numberofproducts").value = numberofproducts;
    let selectedProductList = document.getElementById("selected-products").value;
    if( selectedProductList.search(obj) != -1 ){
        document.getElementById("selected-products").value =  selectedProductList.replace("|"+obj,"");
    }
}

function changeValue(obj){
    let error = obj+"-error";
    document.getElementById(error).innerHTML = "";
    document.getElementById(error).style.display = "none";
    document.getElementById(obj).style = "";
}

