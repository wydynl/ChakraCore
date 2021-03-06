//-------------------------------------------------------------------------------------------------------
// Copyright (C) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE.txt file in the project root for full license information.
//-------------------------------------------------------------------------------------------------------
#include "ParserPch.h"

ParseNode::ParseNode(OpCode nop, charcount_t ichMin, charcount_t ichLim)
{
    this->nop = nop;
    this->grfpn = PNodeFlags::fpnNone;
    this->location = Js::Constants::NoRegister;
    this->emitLabels = false;
    this->isUsed = true;
    this->notEscapedUse = false;
    this->isInList = false;
    this->isCallApplyTargetLoad = false;
    this->isSpecialName = false;
    this->ichMin = ichMin;
    this->ichLim = ichLim;
}

ParseNodeUni * ParseNode::AsParseNodeUni()
{
    Assert(((this->Grfnop() & fnopUni) && this->nop != knopParamPattern) || this->nop == knopThrow);
    return reinterpret_cast<ParseNodeUni *>(this);
}

ParseNodeBin * ParseNode::AsParseNodeBin()
{
    Assert(((this->Grfnop() & fnopBin) && this->nop != knopQmark && this->nop != knopCall && this->nop != knopNew) || this->nop == knopList);
    return reinterpret_cast<ParseNodeBin *>(this);
}

ParseNodeTri * ParseNode::AsParseNodeTri()
{
    Assert(this->nop == knopQmark);
    return reinterpret_cast<ParseNodeTri *>(this);
}

ParseNodeInt * ParseNode::AsParseNodeInt()
{
    Assert(this->nop == knopInt);
    return reinterpret_cast<ParseNodeInt *>(this);
}

ParseNodeFloat * ParseNode::AsParseNodeFloat()
{
    Assert(this->nop == knopFlt);
    return reinterpret_cast<ParseNodeFloat *>(this);
}

ParseNodeRegExp * ParseNode::AsParseNodeRegExp()
{
    Assert(this->nop == knopRegExp);
    return reinterpret_cast<ParseNodeRegExp *>(this);
}

ParseNodeVar * ParseNode::AsParseNodeVar()
{
    Assert(this->nop == knopVarDecl || this->nop == knopConstDecl || this->nop == knopLetDecl || this->nop == knopTemp);
    return reinterpret_cast<ParseNodeVar *>(this);
}

ParseNodePid * ParseNode::AsParseNodePid()
{
    Assert(this->nop == knopName || this->nop == knopStr);
    return reinterpret_cast<ParseNodePid *>(this);
}

ParseNodeSpecialName * ParseNode::AsParseNodeSpecialName()
{
    Assert(this->nop == knopName && this->isSpecialName);
    return reinterpret_cast<ParseNodeSpecialName *>(this);
}

ParseNodeExportDefault * ParseNode::AsParseNodeExportDefault()
{
    Assert(this->nop == knopExportDefault);
    return reinterpret_cast<ParseNodeExportDefault *>(this);
}

ParseNodeStrTemplate * ParseNode::AsParseNodeStrTemplate()
{
    Assert(this->nop == knopStrTemplate);
    return reinterpret_cast<ParseNodeStrTemplate *>(this);
}

ParseNodeSuperReference * ParseNode::AsParseNodeSuperReference()
{
    Assert(this->nop == knopDot || this->nop == knopIndex);
    Assert(this->AsParseNodeBin()->pnode1 && this->AsParseNodeBin()->pnode1->isSpecialName && this->AsParseNodeBin()->pnode1->AsParseNodeSpecialName()->isSuper);
    return reinterpret_cast<ParseNodeSuperReference*>(this);
}

ParseNodeArrLit * ParseNode::AsParseNodeArrLit()
{
    Assert(this->nop == knopArray || this->nop == knopArrayPattern);
    return reinterpret_cast<ParseNodeArrLit*>(this);
}

ParseNodeCall * ParseNode::AsParseNodeCall()
{
    Assert(this->nop == knopCall || this->nop == knopNew);
    return reinterpret_cast<ParseNodeCall*>(this);
}

ParseNodeSuperCall * ParseNode::AsParseNodeSuperCall()
{
    Assert(this->nop == knopCall && this->AsParseNodeCall()->isSuperCall);
    return reinterpret_cast<ParseNodeSuperCall*>(this);
}

ParseNodeClass * ParseNode::AsParseNodeClass()
{
    Assert(this->nop == knopClassDecl);
    return reinterpret_cast<ParseNodeClass*>(this);
}

ParseNodeParamPattern * ParseNode::AsParseNodeParamPattern()
{
    Assert(this->nop == knopParamPattern);
    return reinterpret_cast<ParseNodeParamPattern*>(this);
}

ParseNodeStmt * ParseNode::AsParseNodeStmt()
{
    Assert(this->nop == knopBlock || this->nop == knopBreak || this->nop == knopContinue || this->nop == knopWith || this->nop == knopIf || this->nop == knopSwitch || this->nop == knopCase || this->nop == knopReturn
        || this->nop == knopTryFinally || this->nop == knopTryCatch || this->nop == knopTry || this->nop == knopCatch || this->nop == knopFinally
        || this->nop == knopWhile || this->nop == knopDoWhile || this->nop == knopFor || this->nop == knopForIn || this->nop == knopForOf);
    return reinterpret_cast<ParseNodeStmt*>(this);
}

ParseNodeBlock * ParseNode::AsParseNodeBlock()
{
    Assert(this->nop == knopBlock);
    return reinterpret_cast<ParseNodeBlock*>(this);
}

ParseNodeJump * ParseNode::AsParseNodeJump()
{
    Assert(this->nop == knopBreak || this->nop == knopContinue);
    return reinterpret_cast<ParseNodeJump*>(this);
}

ParseNodeWith * ParseNode::AsParseNodeWith()
{
    Assert(this->nop == knopWith);
    return reinterpret_cast<ParseNodeWith*>(this);
}

ParseNodeIf * ParseNode::AsParseNodeIf()
{
    Assert(this->nop == knopIf);
    return reinterpret_cast<ParseNodeIf*>(this);
}

ParseNodeSwitch * ParseNode::AsParseNodeSwitch()
{
    Assert(this->nop == knopSwitch);
    return reinterpret_cast<ParseNodeSwitch*>(this);
}

ParseNodeCase * ParseNode::AsParseNodeCase()
{
    Assert(this->nop == knopCase);
    return reinterpret_cast<ParseNodeCase*>(this);
}

ParseNodeReturn * ParseNode::AsParseNodeReturn()
{
    Assert(this->nop == knopReturn);
    return reinterpret_cast<ParseNodeReturn*>(this);
}

ParseNodeTryFinally * ParseNode::AsParseNodeTryFinally()
{
    Assert(this->nop == knopTryFinally);
    return reinterpret_cast<ParseNodeTryFinally*>(this);
}

ParseNodeTryCatch * ParseNode::AsParseNodeTryCatch()
{
    Assert(this->nop == knopTryCatch);
    return reinterpret_cast<ParseNodeTryCatch*>(this);
}

ParseNodeTry * ParseNode::AsParseNodeTry()
{
    Assert(this->nop == knopTry);
    return reinterpret_cast<ParseNodeTry*>(this);
}

ParseNodeCatch * ParseNode::AsParseNodeCatch()
{
    Assert(this->nop == knopCatch);
    return reinterpret_cast<ParseNodeCatch*>(this);
}

ParseNodeFinally * ParseNode::AsParseNodeFinally()
{
    Assert(this->nop == knopFinally);
    return reinterpret_cast<ParseNodeFinally*>(this);
}

ParseNodeLoop * ParseNode::AsParseNodeLoop()
{
    Assert(this->nop == knopWhile || this->nop == knopDoWhile || this->nop == knopFor || this->nop == knopForIn || this->nop == knopForOf);
    return reinterpret_cast<ParseNodeLoop*>(this);
}

ParseNodeWhile * ParseNode::AsParseNodeWhile()
{
    Assert(this->nop == knopWhile || this->nop == knopDoWhile);
    return reinterpret_cast<ParseNodeWhile*>(this);
}

ParseNodeFor * ParseNode::AsParseNodeFor()
{
    Assert(this->nop == knopFor);
    return reinterpret_cast<ParseNodeFor*>(this);
}

ParseNodeForInOrForOf * ParseNode::AsParseNodeForInOrForOf()
{
    Assert(this->nop == knopForIn || this->nop == knopForOf);
    return reinterpret_cast<ParseNodeForInOrForOf*>(this);
}

ParseNodeFnc * ParseNode::AsParseNodeFnc()
{
    Assert(this->nop == knopFncDecl || this->nop == knopProg || this->nop == knopModule);
    return reinterpret_cast<ParseNodeFnc*>(this);
}

ParseNodeProg * ParseNode::AsParseNodeProg()
{
    Assert(this->nop == knopProg);
    return reinterpret_cast<ParseNodeProg*>(this);
}

ParseNodeModule * ParseNode::AsParseNodeModule()
{
    // TODO: Currently there is not way to distingish a ParseNodeModule to ParseNodeProg node
    Assert(this->nop == knopProg);
    return reinterpret_cast<ParseNodeModule*>(this);
}

IdentPtr ParseNode::name()
{
    if (this->nop == knopName || this->nop == knopStr)
    {
        return this->AsParseNodePid()->pid;
    }
    else if (this->nop == knopVarDecl || this->nop == knopConstDecl)
    {
        return this->AsParseNodeVar()->pid;
    }
    return nullptr;
}

ParseNodePtr ParseNode::GetFormalNext()
{
    ParseNodePtr pnodeNext = nullptr;

    if (nop == knopParamPattern)
    {
        pnodeNext = this->AsParseNodeParamPattern()->pnodeNext;
    }
    else
    {
        Assert(IsVarLetOrConst());
        pnodeNext = this->AsParseNodeVar()->pnodeNext;
    }
    return pnodeNext;
}

ParseNodeUni::ParseNodeUni(OpCode nop, charcount_t ichMin, charcount_t ichLim, ParseNode * pnode1)
    : ParseNode(nop, ichMin, ichLim)
{
    this->pnode1 = pnode1;
}

ParseNodeBin::ParseNodeBin(OpCode nop, charcount_t ichMin, charcount_t ichLim, ParseNode * pnode1, ParseNode * pnode2)
    : ParseNode(nop, ichMin, ichLim)
{
    this->pnodeNext = nullptr;
    this->pnode1 = pnode1;
    this->pnode2 = pnode2;

    // Statically detect if the add is a concat
    if (!PHASE_OFF1(Js::ByteCodeConcatExprOptPhase))
    {
        // We can't flatten the concat expression if the LHS is not a flatten concat already
        // e.g.  a + (<str> + b)
        //      Side effect of ToStr(b) need to happen first before ToStr(a)
        //      If we flatten the concat expression, we will do ToStr(a) before ToStr(b)
        if ((nop == knopAdd) && (pnode1->CanFlattenConcatExpr() || pnode2->nop == knopStr))
        {
            this->grfpn |= fpnCanFlattenConcatExpr;
        }
    }
}

ParseNodeTri::ParseNodeTri(OpCode nop, charcount_t ichMin, charcount_t ichLim)
    : ParseNode(nop, ichMin, ichLim)
{
}

ParseNodeInt::ParseNodeInt(charcount_t ichMin, charcount_t ichLim, int32 lw)
    : ParseNode(knopInt, ichMin, ichLim)
{
    this->lw = lw;
}

ParseNodeFloat::ParseNodeFloat(OpCode nop, charcount_t ichMin, charcount_t ichLim)
    : ParseNode(nop, ichMin, ichLim)
{
}

ParseNodeRegExp::ParseNodeRegExp(OpCode nop, charcount_t ichMin, charcount_t ichLim)
    : ParseNode(nop, ichMin, ichLim)
{
    this->regexPattern = nullptr;
    this->regexPatternIndex = 0;
}

ParseNodePid::ParseNodePid(OpCode nop, charcount_t ichMin, charcount_t ichLim, IdentPtr pid)
    : ParseNode(nop, ichMin, ichLim)
{
    this->pid = pid;
    this->sym = nullptr;
    this->symRef = nullptr;
}

ParseNodeVar::ParseNodeVar(OpCode nop, charcount_t ichMin, charcount_t ichLim, IdentPtr name)
    : ParseNode(nop, ichMin, ichLim)
{
    Assert(nop == knopVarDecl || nop == knopConstDecl || nop == knopLetDecl || nop == knopTemp);

    this->pid = name;
    this->pnodeInit = nullptr;
    this->pnodeNext = nullptr;
    this->sym = nullptr;
    this->symRef = nullptr;
    this->isSwitchStmtDecl = false;
    this->isBlockScopeFncDeclVar = false;
}

ParseNodeArrLit::ParseNodeArrLit(OpCode nop, charcount_t ichMin, charcount_t ichLim)
    : ParseNodeUni(nop, ichMin, ichLim, nullptr)
{
}

ParseNodeFnc::ParseNodeFnc(OpCode nop, charcount_t ichMin, charcount_t ichLim)
    : ParseNode(nop, ichMin, ichLim)
{
}

ParseNodeClass::ParseNodeClass(OpCode nop, charcount_t ichMin, charcount_t ichLim)
    : ParseNode(nop, ichMin, ichLim)
{
}

ParseNodeExportDefault::ParseNodeExportDefault(OpCode nop, charcount_t ichMin, charcount_t ichLim)
    : ParseNode(nop, ichMin, ichLim)
{
}

ParseNodeStrTemplate::ParseNodeStrTemplate(OpCode nop, charcount_t ichMin, charcount_t ichLim)
    : ParseNode(nop, ichMin, ichLim)
{
}

ParseNodeProg::ParseNodeProg(OpCode nop, charcount_t ichMin, charcount_t ichLim)
    : ParseNodeFnc(nop, ichMin, ichLim)
{
}

ParseNodeModule::ParseNodeModule(OpCode nop, charcount_t ichMin, charcount_t ichLim)
    : ParseNodeProg(nop, ichMin, ichLim)
{
}

ParseNodeCall::ParseNodeCall(OpCode nop, charcount_t ichMin, charcount_t ichLim, ParseNodePtr pnodeTarget, ParseNodePtr pnodeArgs)
    : ParseNode(nop, ichMin, ichLim)
{
    this->pnodeTarget = pnodeTarget;
    this->pnodeArgs = pnodeArgs;
    this->argCount = 0;
    this->spreadArgCount = 0;
    this->callOfConstants = false;
    this->isApplyCall = false;
    this->isEvalCall = false;
    this->isSuperCall = false;
    this->hasDestructuring = false;
}

ParseNodeStmt::ParseNodeStmt(OpCode nop, charcount_t ichMin, charcount_t ichLim)
    : ParseNode(nop, ichMin, ichLim)
{

}

ParseNodeBlock::ParseNodeBlock(charcount_t ichMin, charcount_t ichLim, int blockId, PnodeBlockType blockType)
    : ParseNodeStmt(knopBlock, ichMin, ichLim)
{
    this->pnodeScopes = nullptr;
    this->pnodeNext = nullptr;
    this->scope = nullptr;
    this->enclosingBlock = nullptr;
    this->pnodeLexVars = nullptr;
    this->pnodeStmt = nullptr;
    this->pnodeLastValStmt = nullptr;

    this->callsEval = false;
    this->childCallsEval = false;
    this->blockType = blockType;
    this->blockId = blockId;

    if (blockType != PnodeBlockType::Regular)
    {
        this->grfpn |= PNodeFlags::fpnSyntheticNode;
    }
}

ParseNodeJump::ParseNodeJump(OpCode nop, charcount_t ichMin, charcount_t ichLim)
    : ParseNodeStmt(nop, ichMin, ichLim)
{
}

ParseNodeLoop::ParseNodeLoop(OpCode nop, charcount_t ichMin, charcount_t ichLim)
    : ParseNodeStmt(nop, ichMin, ichLim)
{
}

ParseNodeWhile::ParseNodeWhile(OpCode nop, charcount_t ichMin, charcount_t ichLim)
    : ParseNodeLoop(nop, ichMin, ichLim)
{
}

ParseNodeWith::ParseNodeWith(OpCode nop, charcount_t ichMin, charcount_t ichLim)
    : ParseNodeStmt(nop, ichMin, ichLim)
{
}

ParseNodeParamPattern::ParseNodeParamPattern(OpCode nop, charcount_t ichMin, charcount_t ichLim)
    : ParseNode(nop, ichMin, ichLim)
{
}

ParseNodeIf::ParseNodeIf(OpCode nop, charcount_t ichMin, charcount_t ichLim)
    : ParseNodeStmt(nop, ichMin, ichLim)
{
}

ParseNodeForInOrForOf::ParseNodeForInOrForOf(OpCode nop, charcount_t ichMin, charcount_t ichLim)
    : ParseNodeLoop(nop, ichMin, ichLim)
{
}

ParseNodeFor::ParseNodeFor(OpCode nop, charcount_t ichMin, charcount_t ichLim)
    : ParseNodeLoop(nop, ichMin, ichLim)
{
}

ParseNodeSwitch::ParseNodeSwitch(OpCode nop, charcount_t ichMin, charcount_t ichLim)
    : ParseNodeStmt(nop, ichMin, ichLim)
{
}

ParseNodeCase::ParseNodeCase(OpCode nop, charcount_t ichMin, charcount_t ichLim)
    : ParseNodeStmt(nop, ichMin, ichLim)
{
}

ParseNodeReturn::ParseNodeReturn(OpCode nop, charcount_t ichMin, charcount_t ichLim)
    : ParseNodeStmt(nop, ichMin, ichLim)
{
}

ParseNodeTryFinally::ParseNodeTryFinally(OpCode nop, charcount_t ichMin, charcount_t ichLim)
    : ParseNodeStmt(nop, ichMin, ichLim)
{
}

ParseNodeTryCatch::ParseNodeTryCatch(OpCode nop, charcount_t ichMin, charcount_t ichLim)
    : ParseNodeStmt(nop, ichMin, ichLim)
{
}

ParseNodeTry::ParseNodeTry(OpCode nop, charcount_t ichMin, charcount_t ichLim)
    : ParseNodeStmt(nop, ichMin, ichLim)
{
}

ParseNodeCatch::ParseNodeCatch(OpCode nop, charcount_t ichMin, charcount_t ichLim)
    : ParseNodeStmt(nop, ichMin, ichLim)
{
}

ParseNodeFinally::ParseNodeFinally(OpCode nop, charcount_t ichMin, charcount_t ichLim)
    : ParseNodeStmt(nop, ichMin, ichLim)
{
}

ParseNodeSpecialName::ParseNodeSpecialName(charcount_t ichMin, charcount_t ichLim, IdentPtr pid)
    : ParseNodePid(knopName, ichMin, ichLim, pid)
{
    this->isSpecialName = true;
    this->isThis = false;
    this->isSuper = false;
}

ParseNodeSuperReference::ParseNodeSuperReference(OpCode nop, charcount_t ichMin, charcount_t ichLim, ParseNode * pnode1, ParseNode * pnode2)
    : ParseNodeBin(nop, ichMin, ichLim, pnode1, pnode2)
{
    this->pnodeThis = nullptr;
}

ParseNodeSuperCall::ParseNodeSuperCall(OpCode nop, charcount_t ichMin, charcount_t ichLim, ParseNode * pnodeTarget, ParseNode * pnodeArgs)
    : ParseNodeCall(nop, ichMin, ichLim, pnodeTarget, pnodeArgs)
{
    this->isSuperCall = true;
    this->pnodeThis = nullptr;
    this->pnodeNewTarget = nullptr;
}