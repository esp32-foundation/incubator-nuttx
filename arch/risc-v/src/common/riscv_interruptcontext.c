/****************************************************************************
 * arch/risc-v/src/common/riscv_interruptcontext.c
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdbool.h>
#include <nuttx/arch.h>
#include <nuttx/irq.h>

#include "riscv_internal.h"

/****************************************************************************
 * Private Types
 ****************************************************************************/

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: up_interrupt_context
 *
 * Description: Return true is we are currently executing in
 * the interrupt handler context.
 ****************************************************************************/

bool up_interrupt_context(void)
{
#ifdef CONFIG_ARCH_RV64
#ifdef CONFIG_SMP
  irqstate_t flags = up_irq_save();
#endif

  bool ret = CURRENT_REGS != NULL;

#ifdef CONFIG_SMP
  up_irq_restore(flags);
#endif

  return ret;
#else
  return g_current_regs != NULL;
#endif
}
