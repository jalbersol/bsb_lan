// Add custom code for setup function here which will be included at the end of the global section

#ifdef HIDE_PARAMETERS || ifdef FAVORITES
const int NO_PARAMETER = -1;
#endif

#ifdef HIDE_PARAMETERS
bool hide_enabled = true;

size_t hide_size = 128;
int *parameters_skip = NULL;
int hide_position = 0;

void hide_clear_parameter()
{
	hide_enabled = false;
	hide_position = 0;
	hide_size = 0;
	DebugOutput.print(F(" -> Hide: Forget unsupported parameters "));
	free(parameters_skip);
	parameters_skip = NULL;
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

	size_t parameters_keep_len = sizeof(parameters_keep) / sizeof(parameters_keep[0]);
	for (int i = 0; i < parameters_keep_len; i++)
	{
		if (parameters_keep[i] == parameter)
		{
			DebugOutput.print(F(" -> Hide: Not ignored parameter "));
			DebugOutput.println(parameter);
			return false;
		}
	}

	if (!parameters_skip) {
		// initialize array
		DebugOutput.println(F(" -> Hide: Initialize memory"));
		parameters_skip = (int *)calloc(hide_size, sizeof(int));
		for(int i=0; i<hide_size;i++) {
			parameters_skip[i] = NO_PARAMETER;
		}
		hide_position = 0;
		hide_enabled = true;
	} else if (hide_position + 1 > hide_size) {
		// resize array
		hide_enabled = false;
		size_t hide_size_old = hide_size;
		size_t hide_size_new = hide_size_old + 64;
		int *parameters_skip_old = parameters_skip;
		parameters_skip = (int *)calloc(hide_size_new, sizeof(int));
		if (parameters_skip)
		{
			for(int i = hide_size_old+1; i<hide_size_new;i++) { // init. new memory
				parameters_skip[i] = NO_PARAMETER;
			}
			memcpy(parameters_skip, parameters_skip_old, hide_size_old * sizeof(int));
			free(parameters_skip_old);
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
	parameters_skip[hide_position++] = parameter;
}

bool hide_contains_parameter(int parameter)
{
	size_t parameters_keep_len = sizeof(parameters_keep) / sizeof(parameters_keep[0]);
	for (int i = 0; i < parameters_keep_len; i++)
	{
		if (parameters_keep[i] == parameter)
		{
			DebugOutput.print(F(" -> Hide: Not ignored parameter "));
			DebugOutput.println(parameter);
			return false;
		}
	}

	size_t parameters_hide_len = sizeof(parameters_hide) / sizeof(parameters_hide[0]);
	for (int i = 0; i < parameters_hide_len; i++)
	{
		if (parameters_hide[i] == parameter)
		{
			DebugOutput.print(F(" -> Hide: Skip ignored parameter "));
			DebugOutput.println(parameter);
			return true;
		}
	}

	if(!hide_enabled) return false;
	if (!parameters_skip) return false;

	for (int i = 0; i < hide_size; i++) {
		if (parameters_skip[i] == parameter) {
			DebugOutput.print(F(" -> Hide: Skip unsopported parameter "));
			DebugOutput.println(parameter);
			return true;
		}
	}

	return false;
}
#endif // HIDE_PARAMETERS

#ifdef HIDE_CATEGORIES
boolean ignoreCategory(int category)
{
	size_t length = sizeof(categories_hide) / sizeof(categories_hide[0]);
	for (int i = 0; i < length; i++)
	{
		if (categories_hide[i] == category)
		{
			DebugOutput.print(F(" -> Skip category "));
			DebugOutput.println(category);
			return true;
		}
	}
	return false;
}
#endif // HIDE_CATEGORIES

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
