Использован небуфферизированный ввод/вывод. Чтобы файл не был открыт постоянно, пока происходит считывание чисел, или не открывался/закрывался при каждом новом считывании, данные заносятся в массив, затем единожды открывается файл, все данные записываются в него, после файл закрывается.