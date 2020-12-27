// Add custom code for setup function here which will be included at the end of the global section

#ifdef HIDE_PARAMETERS || ifdef FAVORITES
const int NO_PARAMETER = -1;
#endif

#ifdef HIDE_PARAMETERS
bool hide_enabled = true;

size_t hide_size = 128;
int *hide_parameters = NULL;
int hide_position = 0;

void hide_clear_parameter()
{
	hide_enabled = false;
	hide_position = 0;
	hide_size = 0;
	DebugOutput.print(F(" -> Hide: Forget unsupported parameters "));
	free(hide_parameters);
	hide_parameters = NULL;
	hide_size = 128;
	hide_enabled = true;
}

void hide_add_parameter(int parameter)
{
	if(!hide_enabled) return;

	DebugOutput.print(F("  -> Hide: Add unsupported parameter "));
	DebugOutput.print(parameter);
	DebugOutput.print(" #");
	DebugOutput.println(hide_position + 1);

	size_t not_ignore_size = sizeof(not_ignore_parameters) / sizeof(not_ignore_parameters[0]);
	for (int i = 0; i < not_ignore_size; i++)
	{
		if (not_ignore_parameters[i] == parameter)
		{
			DebugOutput.print(F(" -> Hide: Not ignored parameter "));
			DebugOutput.println(parameter);
			return false;
		}
	}

	if (!hide_parameters) {
		// initialize array
		DebugOutput.println(F(" -> Hide: Initialize memory"));
		hide_parameters = (int *)calloc(hide_size, sizeof(int));
		for(int i=0; i<hide_size;i++) {
			hide_parameters[i] = NO_PARAMETER;
		}
		hide_position = 0;
		hide_enabled = true;
	} else if (hide_position + 1 > hide_size) {
		// resize array
		hide_enabled = false;
		size_t hide_size_old = hide_size;
		size_t hide_size_new = hide_size_old + 64;
		int *hide_parameters_old = hide_parameters;
		hide_parameters = (int *)calloc(hide_size_new, sizeof(int));
		if (hide_parameters)
		{
			for(int i = hide_size_old+1; i<hide_size_new;i++) { // init. new memory
				hide_parameters[i] = NO_PARAMETER;
			}
			memcpy(hide_parameters, hide_parameters_old, hide_size_old * sizeof(int));
			free(hide_parameters_old);
			hide_size = hide_size_new;
			hide_enabled = true;
			DebugOutput.print(F(" -> Hide: Resize memory to "));
			DebugOutput.println(hide_size);
		}
		else
		{
			DebugOutput.print(F(" -> Hide: Memory full!"));
			return;
		}
	}
	// add parameter
	hide_parameters[hide_position++] = parameter;
}

bool hide_contains_parameter(int parameter)
{
	size_t not_ignore_size = sizeof(not_ignore_parameters) / sizeof(not_ignore_parameters[0]);
	for (int i = 0; i < not_ignore_size; i++)
	{
		if (not_ignore_parameters[i] == parameter)
		{
			DebugOutput.print(F(" -> Hide: Not ignored parameter "));
			DebugOutput.println(parameter);
			return false;
		}
	}

	size_t ignore_size = sizeof(ignore_parameters) / sizeof(ignore_parameters[0]);
	for (int i = 0; i < ignore_size; i++)
	{
		if (ignore_parameters[i] == parameter)
		{
			DebugOutput.print(F(" -> Hide: Skip ignored parameter "));
			DebugOutput.println(parameter);
			return true;
		}
	}

	if(!hide_enabled) return false;
	if (!hide_parameters) return false;

	for (int i = 0; i < hide_size; i++) {
		if (hide_parameters[i] == parameter) {
			DebugOutput.print(F(" -> Hide: Skip unsopported parameter "));
			DebugOutput.println(parameter);
			return true;
		}
	}

	return false;
}
#endif // HIDE_PARAMETERS

#ifdef HIDE_CATEGORY
boolean ignoreCategory(int category)
{
	size_t length = sizeof(ignore_categories) / sizeof(ignore_categories[0]);
	for (int i = 0; i < length; i++)
	{
		if (ignore_categories[i] == category)
		{
			DebugOutput.print(F(" -> Skip category "));
			DebugOutput.println(category);
			return true;
		}
	}
	return false;
}
#endif // HIDE_CATEGORY

#ifdef FAVORITES
int getReqNumber(char *p)
{
	DebugOutput.print(" p=");//tmp
	DebugOutput.println(p);//tmp
//	p += addChars;
	if (isdigit(p[0]))
	{										 // now we check for digits - nice
		int num = atoi(p); // convert until non-digit char is found
/*		if (0 <= num <= 9)
			p += 1; // log10
		else if (10 <= num <= 99)
			p += 2;
		else if (100 <= num <= 999)
			p += 3;
		else if (1000 <= num <= 9999)
			p += 4;
		else if (10000 <= num <= 99999)
			p += 5;
		else if (100000 <= num <= 999999)
			p += 6;
		else if (1000000 <= num <= 9999999)
			p += 7;
		else if (10000000 <= num <= 99999999)
			p += 8;
		else if (100000000 <= num <= 999999999)
			p += 9;
		else if (1000000000 <= num <= 9999999999)
			p += 10;*/
		return num;
	}
	else
	{
//		p -= addChars;
		return -1;
	}
}
#endif
